#include "file_handle.h"

#include <fstream>
#include <iostream>

FileHandle::FileHandle() : m_default_path("./../logs/last_save.txt"), m_auto_save(AutoSaveMode::ON) {
	m_path = m_default_path;
}

FileHandle::FileHandle(const std::string& path) : m_path(path), m_auto_save(AutoSaveMode::ON) {
	if(m_path == "") {
		m_path = m_default_path;
	}
}

void FileHandle::set_auto_save(AutoSaveMode mode) {
	m_auto_save = mode;
}

void FileHandle::save(const ActionHandle& ah, const std::string& path) const {
	std::string open_path = path;

	if(open_path == "") {
		open_path = m_path;
	}

	std::string content = "";

	content += "DEFINES{\n";
	
	for(int idx = 0; idx < ah.functions().size(); idx++) {
		HashNode<Pair<std::string, LogicalTree<std::string>>>* node = ah.functions().map()[idx];

		while(node != nullptr) {

			content += "\t" + node->key;
			content += "{\n";

			content += "\t\t" + node->value.first + "\n";

			content += "\t\t";
			content += node->value.second;
			content += "\n";

			content += "\t}\n";
	
			node = node->next;
		}
	}

	content += "}\n";

	content += "SOLVES{\n";
	
	for(int idx = 0; idx < ah.solves().size(); idx++) {
		HashNode<Pair<std::string, bool>>* node = ah.solves().map()[idx];

		while(node != nullptr) {

			content += "\t" + node->key;
			content += "{\n";

			content += "\t\t" + node->value.first + "\n";
			content += "\t\t";
			node->value.second ? content += "1\n" : content += "0\n";

			content += "\t}\n";
	
			node = node->next;
		}
	}

	content += "}\n";

	content += "ALLS{\n";
	
	for(int idx = 0; idx < ah.all_solves().size(); idx++) {
		HashNode<int>* node = ah.all_solves().map()[idx];

		while(node != nullptr) {

			content += "\t" + node->key;
			content += "{\n";

			content += "\t\t" + std::to_string(node->value) + "\n";

			content += "\t}\n";

			node = node->next;
		}
	}

	content += "}\n";

	std::ofstream out(open_path, std::ios::out | std::ios::binary);

	if (!out.is_open()) {
		std::cout << "[save ERROR] > Failed to open file '" + open_path + "'\n";
		return;
	}

	out.write(content.data(), content.size());

	out.close();
}

void FileHandle::read(ActionHandle& ah, const std::string& path) const {
	std::string open_path = path;

	if(open_path == "") {
		open_path = m_path;
	}

	std::ifstream in(open_path);

	if (!in.is_open()) {
		std::cout << "[read ERROR] > Failed to open file '" + open_path + "'\n";
		return;
	}


	std::string content = std::string(
		std::istreambuf_iterator<char>(in),
		std::istreambuf_iterator<char>()
	);

	if(content == "") {
		std::cout << "[read ERROR] > Unexpected error\n";
		return;
	};

	StringArray line_conent = StringHandle::split(content, '\n');

	for(long long idx = 0; idx < line_conent.count(); idx++) {
		std::string& line = line_conent.data()[idx];


		std::string name = "";

		if(StringHandle::contains(line, '{')) {
			name = StringHandle::remove_symbol(line, '\t');
			name = StringHandle::remove_symbol(name, '{');

			std::string func_name = "";

			int depth = 1;

			if(name == "DEFINES") {
				while(depth > 0) {
					line = line_conent.data()[++idx];

					if(StringHandle::contains(line, '{')) {
						func_name = StringHandle::remove_symbol(line, '\t');
						func_name = StringHandle::remove_symbol(func_name, '{');

						depth++;
						continue;
					}
					else if(StringHandle::contains(line, '}')) {
						depth--;
						continue;
					}
					else if(line != "\n") {
						std::string first    = StringHandle::remove_symbol(line, '\t');
						std::string s_second = line_conent.data()[++idx];

						s_second = StringHandle::remove_symbol(s_second, '\t');
						s_second = StringHandle::remove_symbol(s_second, ' ');

						StringArray second;

						for(int in_idx = 0; in_idx < s_second.size(); in_idx++){ 
							second.push_back(s_second[in_idx]);
						}

						LogicalTree<std::string> func;

						func.build(second, ah.functions());

						ah.functions().insert(
							func_name,
							Pair<std::string, LogicalTree<std::string>>(
								first,
								func
							)
						);
					}
				}
			}

			else if(name == "SOLVES") {
				while(depth > 0) {
					line = line_conent.data()[++idx];

					if(StringHandle::contains(line, '{')) {
						func_name = StringHandle::remove_symbol(line, '\t');
						func_name = StringHandle::remove_symbol(func_name, '{');

						depth++;
						continue;
					}
					else if(StringHandle::contains(line, '}')) {
						depth--;
						continue;
					}
					else if(line != "\n") {
						std::string first = StringHandle::remove_symbol(line, '\t');;
						std::string s_second = line_conent.data()[++idx];

						bool second = false;

						s_second = StringHandle::remove_symbol(s_second, '\t');

						if(s_second[0] == '1') {
							second = true;
						}

						StringArray val_sa;

						ah.solves().insert(
							func_name,
							Pair<std::string, bool>(
								first,
								second
							)
						);
					}
				}
			}

			else if(name == "ALLS") {
				while(depth > 0) {
					line = line_conent.data()[++idx];

					if(StringHandle::contains(line, '{')) {
						func_name = StringHandle::remove_symbol(line, '\t');
						func_name = StringHandle::remove_symbol(func_name, '{');

						depth++;
						continue;
					}
					else if(StringHandle::contains(line, '}')) {
						depth--;
						continue;
					}
					else if(line != "\n") {
						std::string first = StringHandle::remove_symbol(line, '\t');

						ah.all_solves().insert(
							func_name,
							StringHandle::to_int(first)
						);
					}
				}
			}
		}
	}
	return;
}

void FileHandle::leave_check(const ActionHandle& ah) const {
	if(m_auto_save != AutoSaveMode::ON) {
		return;
	}

	save(ah);
}

std::string FileHandle::path() const {
	return m_path;
}

std::string FileHandle::default_path() const {
	return m_default_path;
}
