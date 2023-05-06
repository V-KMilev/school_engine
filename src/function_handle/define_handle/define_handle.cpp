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

bool DefineHandle::handle_body(const std::string &body, const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions) {
	StringHandle sh;

	std::string my_valid_symbols = invalid_symbols;

	for(int idx = 0; idx < m_cached_params.count(); idx++) {
		my_valid_symbols = sh.remove_symbol(my_valid_symbols, m_cached_params.data()[idx][0]);
	}

	StringArray body_data = sh.split(body, ' ');
	StringArray fixed_body_data;

	for(int old_idx = 0; old_idx < body_data.count(); old_idx++) {

		if(body_data.data()[old_idx].size() == 1) {
			fixed_body_data.push_back(body_data.data()[old_idx][0]);

			continue;
		}
		else if(
			sh.contains(body_data.data()[old_idx], '!')      ||
			sh.get_count(body_data.data()[old_idx], '(') > 1 ||
			sh.get_count(body_data.data()[old_idx], ')') > 1
		) {

			int split_size = body_data.data()[old_idx].size();

			for(int new_idx = 0; new_idx < split_size; new_idx++) {
				fixed_body_data.push_back(body_data.data()[old_idx][new_idx]);
			}

			continue;
		}

		std::string func_name = sh.extract_string_between_ic(body_data.data()[old_idx], 0, '(');
		body_data.data()[old_idx] = func_name;

		std::cerr << "\n" << functions.get(func_name).first << "\n";
	}

	m_function.build(fixed_body_data, functions);

	m_function.print();

	return true;
}
