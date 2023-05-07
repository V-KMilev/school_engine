#include "define_handle.h"

#include <iostream>
#include <string>

#include "post.h"

#include "string_handle.h"

#include "logical_tree.h"

DefineHandle::DefineHandle(const std::string &name) {
	m_name = name;
	m_in_order = "";
}
DefineHandle::DefineHandle() {
	m_name = "";
	m_in_order = "";
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

		m_in_order += param;
	}

	return true;
}

bool DefineHandle::handle_body(
	const std::string &body,
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions
) {
	StringHandle sh;

	StringArray body_data = sh.split(body, ' ');
	StringArray clean_body_data(body_data.size());

	HashMap<Pair<std::string, LogicalTree<std::string>>> fixed_functions;

	for(int idx = 0; idx < body_data.count(); idx++) {

		const std::string& current_data = body_data.data()[idx];

		std::string clean_data = "";

		if(single_param(sh, current_data, clean_data, clean_body_data)) {
			continue;
		}

		if(clean_func_param(sh, functions, current_data, clean_data, clean_body_data, fixed_functions)) {
			continue;
		}

		if(!dirty_func_param(sh, functions, current_data, clean_data, clean_body_data, fixed_functions)) {
			std::cerr << "[Function ERROR] > Unexpected error\n";
			return false;
		}
	}
	m_function.build(clean_body_data, fixed_functions);

	return true;
}

bool DefineHandle::single_param(
	const StringHandle& sh,
	const std::string& current_data,
	std::string& clean_data,
	StringArray& clean_body_data
) {
	if(current_data.size() == 1) {

		const char& c = current_data[0];
		clean_body_data.push_back(c);

		return true;
	}

	clean_data = sh.remove_symbol(current_data, '!');
	clean_data = sh.remove_symbol(clean_data,   '(');
	clean_data = sh.remove_symbol(clean_data,   ')');

	if(clean_data.size() == 1) {
		int split_size = current_data.size();

		for(int idx = 0; idx < split_size; idx++) {

			const char& c = current_data[idx];
			clean_body_data.push_back(c);
		}
		return true;
	}

	return false;
}

bool DefineHandle::clean_func_param(
	const StringHandle& sh,
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	const std::string& current_data,
	const std::string& clean_data,
	StringArray& clean_body_data,
	HashMap<Pair<std::string, LogicalTree<std::string>>>& fixed_functions
) {
	std::string current_in_order = "";

	if(!(
		sh.get_count(current_data, '!') > 0 ||
		sh.get_count(current_data, '(') > 1 ||
		sh.get_count(current_data, ')') > 1 
	)) {

		// Remove params without the first param
		std::string func_name = sh.extract_string_between_ic(
			clean_data,
			0,
			','
		);

		// Remove first param
		func_name = sh.extract_string_between_ii(func_name, 0, func_name.size() - 1);

		// Get all params
		current_in_order = sh.extract_string_between_ii(clean_data, func_name.size(), clean_data.size());
		current_in_order = sh.remove_symbol(current_in_order, ',');

		const Pair<std::string, LogicalTree<std::string>>& pair = update_in_func(
			functions,
			func_name,
			current_in_order
		);
		fixed_functions.insert(pair.first, pair);

		clean_body_data.push_back(func_name);
		return true;
	}

	return false;
}

bool DefineHandle::dirty_func_param(
	const StringHandle& sh,
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	const std::string& current_data,
	const std::string& clean_data,
	StringArray& clean_body_data,
	HashMap<Pair<std::string, LogicalTree<std::string>>>& fixed_functions
) {
	std::string current_in_order = "";

	int split_size = current_data.size();

	for(int idx = 0; idx < split_size; idx++) {
		const char& c = current_data[idx];

		if(c != clean_data[0]) {
			clean_body_data.push_back(c);
			continue;
		}

		// Remove front content
		std::string func_name = sh.extract_string_between_ii(
			current_data,
			idx,
			clean_data.size() + 2 + 1
		);

		// Remove extra brackets
		func_name = sh.remove_symbol(func_name, '(');
		func_name = sh.remove_symbol(func_name, ')');

		if(func_name == clean_data) {

			// Remove params
			func_name = sh.extract_string_between_ic(func_name, 0, ',');
			func_name = sh.extract_string_between_ii(func_name, 0, func_name.size() - 1);

			// Get all params
			current_in_order = sh.extract_string_between_ii(clean_data, func_name.size(), clean_data.size());
			current_in_order = sh.remove_symbol(current_in_order, ',');

			const Pair<std::string, LogicalTree<std::string>>& pair = update_in_func(
				functions,
				func_name,
				current_in_order
			);
			fixed_functions.insert(pair.first, pair);

			clean_body_data.push_back(func_name);
			idx += clean_data.size() + 2 - 1;
		}
	}

	return true;
}

Pair<std::string, LogicalTree<std::string>> DefineHandle::update_in_func(
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	const std::string& func_name,
	const std::string& current_in_order
) {

	const std::string& func_in_order = functions.get(func_name).first;

	if(func_in_order == "") {
		std::cerr << "[Function ERROR] > Unexpected error\n";
		return Pair<std::string, LogicalTree<std::string>>();
	}

	if(current_in_order == func_in_order) {
		return Pair<std::string, LogicalTree<std::string>>(
			func_name,
			functions.get(func_name).second
		);
	}

	const TreeNode<std::string>* origin_root = functions.get(func_name).second.get_root();

	TreeNode<std::string>* root = origin_root->m_copy();
	const TreeNode<std::string>* copy = root->m_copy();

	for(int idx = 0; idx < current_in_order.size(); idx++) {

		const char& new_c = current_in_order[idx];
		const char& old_c = func_in_order[idx];

		if(new_c != old_c) {
			root->fix_data(copy, old_c, new_c);
		}
	}

	return Pair<std::string, LogicalTree<std::string>>(
		func_name,
		LogicalTree<std::string>(root)
	);
}
