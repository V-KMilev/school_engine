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
	m_params = params;

	m_params = StringHandle::remove_symbol(m_params, ' ');
	m_params = StringHandle::remove_symbol(m_params, ',');

	if(StringHandle::contains(m_params, invalid_symbols)) {
		std::cerr << "[ERROR] Invaid parameter(s) set!\n";

		return false;
	}

	return true;
}

bool DefineHandle::handle_body(
	const std::string &body,
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions
) {
	StringArray body_data = StringHandle::split(body, ' ');
	StringArray clean_body_data(body_data.size());

	if(!vaild_body(functions, body, body_data)) {
		return false;
	}

	HashMap<Pair<std::string, LogicalTree<std::string>>> fixed_functions;

	for(int idx = 0; idx < body_data.count(); idx++) {

		const std::string& current_data = body_data.data()[idx];

		std::string clean_data = "";

		if(single_param(functions, current_data, clean_data, clean_body_data)) {
			continue;
		}

		if(clean_func_param(functions, current_data, clean_data, clean_body_data, fixed_functions)) {
			continue;
		}

		if(!dirty_func_param(functions, current_data, clean_data, clean_body_data, fixed_functions)) {
			std::cerr << "[dirty_func_param ERROR] > Unexpected error\n";
			return false;
		}
	}

	StringArray post_data = StringHandle::convert_to_postfix(clean_body_data);

	m_function.build(post_data, fixed_functions);

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
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	const std::string& current_data,
	std::string& clean_data,
	StringArray& clean_body_data
) const {
	if(current_data.size() == 1) {
		const char& c = current_data[0];

		clean_body_data.push_back(c);
		return true;
	}

	clean_data = StringHandle::remove_symbol(current_data, '!');
	clean_data = StringHandle::remove_symbol(clean_data,   '(');
	clean_data = StringHandle::remove_symbol(clean_data,   ')');

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
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	const std::string& current_data,
	const std::string& clean_data,
	StringArray& clean_body_data,
	HashMap<Pair<std::string, LogicalTree<std::string>>>& fixed_functions
) const {
	if(!(
		StringHandle::count(current_data, '!') > 0 ||
		StringHandle::count(current_data, '(') > 1 ||
		StringHandle::count(current_data, ')') > 1 
	)) {
		// Remove params without the first param
		std::string func_name = StringHandle::extract_string_between_ic(clean_data, 0, ',');

		// Remove first param
		func_name = StringHandle::extract_string_between_ii(func_name, 0, func_name.size() - 1);

		std::string current_in_order = "";

		// Get all params
		current_in_order = StringHandle::extract_string_between_ii(clean_data, func_name.size(), clean_data.size());
		current_in_order = StringHandle::remove_symbol(current_in_order, ',');

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
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	const std::string& current_data,
	const std::string& clean_data,
	StringArray& clean_body_data,
	HashMap<Pair<std::string, LogicalTree<std::string>>>& fixed_functions
) const {
	int split_size = current_data.size();

	for(int idx = 0; idx < split_size; idx++) {
		const char& c = current_data[idx];

		if(c != clean_data[0]) {
			clean_body_data.push_back(c);
			continue;
		}

		// Remove front content
		std::string func_name = StringHandle::extract_string_between_ii(
			current_data,
			idx,
			clean_data.size() + 2 + 1
		);

		// Remove extra brackets
		func_name = StringHandle::remove_symbol(func_name, '(');
		func_name = StringHandle::remove_symbol(func_name, ')');

		if(func_name == clean_data) {
			// Remove params
			func_name = StringHandle::extract_string_between_ic(func_name, 0, ',');
			func_name = StringHandle::extract_string_between_ii(func_name, 0, func_name.size() - 1);

			std::string current_params = "";

			// Get all params
			current_params = StringHandle::extract_string_between_ii(clean_data, func_name.size(), clean_data.size());
			current_params = StringHandle::remove_symbol(current_params, ',');

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
) const {
	const std::string& func_params = functions.get(func_name).first;

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

		if(new_c != old_c) {
			root->fix_data(copy, old_c, new_c);
		}
	}

	return Pair<std::string, LogicalTree<std::string>>(
		func_name,
		LogicalTree<std::string>(root)
	);
}

bool DefineHandle::vaild_body(
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	const std::string& body,
	const StringArray& body_data
) const {

	if((StringHandle::count(body, '(') + StringHandle::count(body, ')')) % 2 == 1) {
		std::cerr << "[vaild_body ERROR] > Bracket miss-count\n";
		return false;
	}

	for(int idx = 0, depth = 0; idx < body.size(); idx++) {
		if(body[idx] == '(') {
			depth += 1;
		}
		else if(body[idx] == ')') {
			depth -= 1;
		}

		if(depth < 0) {
			std::cerr << "[vaild_body ERROR] > Invaild bracket used\n";
			return false;
		}
	}

	for(int idx = 0; idx < body_data.count(); idx++) {
		const std::string& data = body_data.data()[idx];

		std::string clean_data = "";

		if(data.size() == 0) {
			std::cerr << "[vaild_body ERROR] > Invaild parameter(s) used\n";
			return false;
		}

		if(data.size() == 1) {
			if(!is_valid(functions, data)) {
				std::cerr << "[vaild_body ERROR] > Invaild parameter(s) used\n";
				return false;
			}
		}

		clean_data = StringHandle::remove_symbol(data, '!');
		clean_data = StringHandle::remove_symbol(clean_data, '(');
		clean_data = StringHandle::remove_symbol(clean_data, ')');

		if(clean_data.size() == 0) {
			std::cerr << "[vaild_body ERROR] > Invaild parameter(s) used\n";
			return false;
		}

		if(clean_data.size() == 1) {
			if(!is_valid(functions, clean_data)) {
				std::cerr << "[vaild_body ERROR] > Invaild parameter(s) used\n";
				return false;
			}
		}

		std::string func_name = "";
		std::string func_params = "";

		if(clean_data.size() > 1) {
			func_name = StringHandle::extract_string_between_ic(clean_data, 0, ',');
			func_name = StringHandle::extract_string_between_ii(func_name, 0, func_name.size() - 1);

			if(!is_valid(functions, func_name)) {
				std::cerr << "[vaild_body ERROR] > Undefined function(s) used\n";
				return false;
			}

			func_params = StringHandle::extract_string_between_ii(clean_data, func_name.size(), clean_data.size());
			func_params = StringHandle::remove_symbol(func_params, ',');

			if(m_params.size() != func_params.size()) {
				std::cerr << "[update_in_func ERROR] > In function parameter(s) miss-count\n";
				return false;
			}

			for(int idx = 0; idx < func_params.size(); idx++) {

				if(!StringHandle::contains(m_params, func_params[idx])) {
					std::cerr << "[update_in_func ERROR] > Invalid in function parameter(s) used\n";
					return false;
				}
			}
		}
	}

	return true;
}

bool DefineHandle::is_valid(
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	const std::string& param
) const { 
	if(param.size() == 1) {
		if(StringHandle::contains(param, "&|!()")) {
			return true;
		}
		if(StringHandle::contains(param, m_params)) {
			return true;
		}
	}

	else if(functions.get(param) != Pair<std::string, LogicalTree<std::string>>()) {
		return true;
	}

	return false;
}
