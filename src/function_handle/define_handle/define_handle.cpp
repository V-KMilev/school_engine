#include "define_handle.h"

#include <iostream>
#include <string>

#include "post.h"

#include "string_handle.h"

#include "logical_tree.h"

DefineHandle::DefineHandle(const std::string &name) {
	m_name = name;
	m_params = "";
}
DefineHandle::DefineHandle() {
	m_name = "";
	m_params = "";
}

DefineHandle::DefineHandle(DefineHandle &&move) {
	m_name = move.m_name;
	m_params = move.m_params;
	m_function = std::move(move.m_function);
}

DefineHandle& DefineHandle::operator = (DefineHandle &&move) noexcept {
	m_name = move.m_name;
	m_params = move.m_params;
	m_function = std::move(move.m_function);

	return *this;
}

bool DefineHandle::handle_params(const std::string &params) {
	StringHandle sh;

	m_params = params;

	m_params = sh.remove_symbol(m_params, ' ');
	m_params = sh.remove_symbol(m_params, ',');

	if(sh.contains(m_params, invalid_symbols)) {
		std::cerr << "[ERROR] Invaid parameter(s) set!\n";

		return false;
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

		if(single_param(sh, functions, current_data, clean_data, clean_body_data)) {
			continue;
		}

		if(clean_func_param(sh, functions, current_data, clean_data, clean_body_data, fixed_functions)) {
			continue;
		}

		if(!dirty_func_param(sh, functions, current_data, clean_data, clean_body_data, fixed_functions)) {
			std::cerr << "[dirty_func_param ERROR] > Unexpected error\n";
			return false;
		}
	}
	m_function.build(clean_body_data, fixed_functions);

	return true;
}

const std::string& DefineHandle::get_name() const {
	return m_name;
}

const std::string& DefineHandle::get_params() const {
	return m_params;
}

const LogicalTree<std::string>& DefineHandle::get_function_tree() const {
	return m_function;
}

bool DefineHandle::single_param(
	const StringHandle& sh,
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	const std::string& current_data,
	std::string& clean_data,
	StringArray& clean_body_data
) {
	if(current_data.size() == 1) {

		const char& c = current_data[0];

		if(!is_valid(functions, std::string(1, c))) {
			std::cerr << "[single_param ERROR] > Invalid parameter set\n";
			exit(-1);
		}

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

			if(!is_valid(functions, std::string(1, c))) {
				std::cerr << "[single_param ERROR] > Invalid parameter set\n";
				exit(-1);
			}

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
	if(!(
		sh.get_count(current_data, '!') > 0 ||
		sh.get_count(current_data, '(') > 1 ||
		sh.get_count(current_data, ')') > 1 
	)) {
		// Remove params without the first param
		std::string func_name = sh.extract_string_between_ic(clean_data, 0, ',');

		// Remove first param
		func_name = sh.extract_string_between_ii(func_name, 0, func_name.size() - 1);

		if(!is_valid(functions, func_name)) {
			std::cerr << "[clean_func_param ERROR] > Invalid parameter set\n";
			exit(-1);
		}

		std::string current_in_order = "";

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

	int split_size = current_data.size();

	for(int idx = 0; idx < split_size; idx++) {
		const char& c = current_data[idx];

		if(c != clean_data[0]) {

			if(!is_valid(functions, std::string(1, c))) {
				std::cerr << "[dirty_func_param ERROR] > Invalid parameter set\n";
				exit(-1);
			}

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

			if(!is_valid(functions, func_name)) {
				std::cerr << "[dirty_func_param ERROR] > Invalid parameter set\n";
				exit(-1);
			}

			std::string current_params = "";

			// Get all params
			current_params = sh.extract_string_between_ii(clean_data, func_name.size(), clean_data.size());
			current_params = sh.remove_symbol(current_params, ',');

			const Pair<std::string, LogicalTree<std::string>>& pair = update_in_func(
				functions,
				func_name,
				current_params
			);
			fixed_functions.insert(pair.first, pair);

			clean_body_data.push_back(func_name);

			// Skip to the end of the function
			idx += clean_data.size() + 2 - 1;
		}
	}

	return true;
}

Pair<std::string, LogicalTree<std::string>> DefineHandle::update_in_func(
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	const std::string& func_name,
	const std::string& current_params
) {
	const std::string& func_params = functions.get(func_name).first;

	if(current_params.size() < func_params.size() || current_params.size() > func_params.size()) {
		std::cerr << "[update_in_func ERROR] > Invalid function parameter set\n";
		exit(-1);
	}

	if(current_params == func_params) {
		return Pair<std::string, LogicalTree<std::string>>(
			func_name,
			functions.get(func_name).second
		);
	}

	const TreeNode<std::string>* origin_root = functions.get(func_name).second.get_root();

	TreeNode<std::string>* root = origin_root->m_copy();
	const TreeNode<std::string>* copy = root->m_copy();

	for(int idx = 0; idx < current_params.size(); idx++) {

		const char& new_c = current_params[idx];
		const char& old_c = func_params[idx];

		if(!is_valid(functions, std::string(1, new_c))) {
			std::cerr << "[update_in_func ERROR] > Invalid function parameter set\n";
			exit(-1);
		}

		if(new_c != old_c) {
			root->fix_data(copy, old_c, new_c);
		}
	}

	return Pair<std::string, LogicalTree<std::string>>(
		func_name,
		LogicalTree<std::string>(root)
	);
}

bool DefineHandle::is_valid(
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	const std::string& param
) const { 
	if(param.size() == 1) {
		if(
			param[0] == '&' || param[0] == '|' ||
			param[0] == '(' || param[0] == ')' ||
			param[0] == '!'
		) {
			return true;
		}

		for(int idx = 0; idx < m_params.size(); idx++) {

			if(param[0] == m_params[idx]) {
				return true;
			}
		}
	}

	if(functions.get_count() == 0) {
		return false;
	}

	if(functions.get(param) != Pair<std::string, LogicalTree<std::string>>()) {
		return true;
	}

	return false;
}
