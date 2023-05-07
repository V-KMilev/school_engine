#include "define_handle.h"

#include <iostream>
#include <string>

#include "post.h"

#include "string_handle.h"

#include "logical_tree.h"

DefineHandle::DefineHandle(const std::string &name) {
	 m_name = name;
}
DefineHandle::DefineHandle() {
	m_name = "";
}

DefineHandle::DefineHandle(DefineHandle &&move) {
	m_name = move.m_name;
	m_cached_params = std::move(move.m_cached_params);
	m_function = std::move(move.m_function);
}

DefineHandle& DefineHandle::operator = (DefineHandle &&move) noexcept {
	m_name = move.m_name;
	m_cached_params = std::move(move.m_cached_params);
	m_function = std::move(move.m_function);

	return *this;
}

bool DefineHandle::handle_params(const std::string &params) {
	StringHandle sh;

	m_cached_params = sh.split(params, ',');

	for(int idx = 0; idx < m_cached_params.count(); idx++) {

		std::string& param = m_cached_params.data()[idx];

		if((param[0] >= '!' && param[0] <= '@')  ||
			(param[0] >= '[' && param[0] <= '`') ||
			(param[0] >= '{' && param[0] <= '~')
		) {
			std::cerr << "[ERROR] Invaid parameter(s) set!\n";

			return false;
		}

		if(sh.contains(param, ' ')) {
			param = sh.remove_symbol(param, ' ');
		}

		if(sh.contains(param, invalid_symbols)) {
			std::cerr << "[ERROR] Invaid parameter(s) set!\n";

			return false;
		}
	}

	return true;
}

bool DefineHandle::handle_body(const std::string &body, const HashMap<LogicalTree<std::string>>& functions) {
	StringHandle sh;

	std::string my_valid_symbols = invalid_symbols;

	for(int idx = 0; idx < m_cached_params.count(); idx++) {
		my_valid_symbols = sh.remove_symbol(my_valid_symbols, m_cached_params.data()[idx][0]);
	}

	StringArray body_data = sh.split(body, ' ');
	StringArray clean_body_data(body_data.size());

	for(int first_idx = 0; first_idx < body_data.count(); first_idx++) {

		const std::string& current_data = body_data.data()[first_idx];

		std::string clean_data = "";

		if(current_data.size() == 1) {

			const char& c = current_data[0];
			clean_body_data.push_back(c);

			continue;
		}

		clean_data = sh.remove_symbol(current_data, '!');
		clean_data = sh.remove_symbol(clean_data,   '(');
		clean_data = sh.remove_symbol(clean_data,   ')');

		if(clean_data.size() == 1) {
			int split_size = current_data.size();

			for(int second_idx = 0; second_idx < split_size; second_idx++) {

				const char& c = current_data[second_idx];
				clean_body_data.push_back(c);
			}
			continue;
		}

		if(!(
			sh.get_count(current_data, '!') > 0 ||
			sh.get_count(current_data, '(') > 1 ||
			sh.get_count(current_data, ')') > 1 
		)) {
			std::string func_name = sh.extract_string_between_ic(clean_data, 0, ',');

			func_name = sh.extract_string_between_ii(func_name, 0, func_name.size() - 1);

			clean_body_data.push_back(func_name);
			continue;
		}

		int split_size = current_data.size();

		for(int second_idx = 0; second_idx < split_size; second_idx++) {

			const char& c = current_data[second_idx];

			if(c != clean_data[0]) {

				clean_body_data.push_back(c);
				continue;
			}

			std::string func_name = sh.extract_string_between_ii(current_data, second_idx, clean_data.size() + 2 + 1);

			func_name = sh.remove_symbol(func_name, '(');
			func_name = sh.remove_symbol(func_name, ')');

			if(func_name == clean_data) {

				func_name = sh.extract_string_between_ic(func_name, 0, ',');
				func_name = sh.extract_string_between_ii(func_name, 0, func_name.size() - 1);

				clean_body_data.push_back(func_name);
				second_idx += clean_data.size() + 2 - 1;
			}
		}
	}

	m_function.build(clean_body_data, functions);

	m_function.print();

	return true;
}
