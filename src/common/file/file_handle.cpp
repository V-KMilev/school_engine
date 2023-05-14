#include "file_handle.h"

#include <fstream>
#include <iostream>

FileHandle::FileHandle() : m_path("./../logs/last_save.txt"), m_auto_save(AutoSaveMode::ON) {}

FileHandle::FileHandle(const std::string& path) : m_path(path), m_auto_save(AutoSaveMode::ON) {}

void FileHandle::set_auto_save(AutoSaveMode mode) {
	m_auto_save = mode;
}

void FileHandle::save(const ActionHandle& ah, const std::string& path) const {

	std::string content = "";

	content += "DEFINES{\n";
	
	for(int idx = 0; idx < ah.get_functions().size(); idx++) {
		HashNode<Pair<std::string, LogicalTree<std::string>>>* node = ah.get_functions().map()[idx];

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

	content += "\n";

	content += "SOLVES{\n";
	
	for(int idx = 0; idx < ah.get_solves().size(); idx++) {
		HashNode<Pair<std::string, bool>>* node = ah.get_solves().map()[idx];

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

	content += "\n";

	content += "ALLS{\n";
	
	for(int idx = 0; idx < ah.get_all_solves().size(); idx++) {
		HashNode<int>* node = ah.get_all_solves().map()[idx];

		while(node != nullptr) {

			content += "\t" + node->key;
			content += "{\n";

			content += "\t\t" + std::to_string(node->value) + "\n";

			content += "\t}\n";

			node = node->next;
		}
	}

	content += "}\n";

	// std::string open_path = path;
	std::string open_path = m_path;

	// if(open_path == "") {
	// 	open_path = m_path;
	// }

	std::ofstream out(open_path, std::ios::out | std::ios::binary);

	if (!out.is_open()) {
		std::cout << "[handle_type ERROR] > Failed to open file '" + m_path + "'\n";
		return;
	}

	out.write(content.data(), content.size());

	out.close();
}

ActionHandle FileHandle::read() const {
	ActionHandle ah;
	return ah;
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
