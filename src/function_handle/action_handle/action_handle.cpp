#include "action_handle.h"

#include <iostream>

#include "string_handle.h"
#include "post.h"

#include "define_handle.h"
#include "solve_handle.h"

bool ActionHandle::handle_input(const std::string &content) {
	StringHandle sh;

	StringArray type;

	std::string params;
	std::string name;
	std::string body;

	std::string fixed_content = remove_white_spaces(content);

	type = sh.split_limit(fixed_content, ' ', 6);

	if(!handle_type(type.data()[0])) {
		return false;
	}

	fixed_content = remove_white_spaces(type.data()[1]);

	name = sh.extract_string_between_ic(fixed_content, 0, '(');
	params = sh.extract_string_between_cc(fixed_content, '(', ')');

	if(!handle_name(name)) {
		return false;
	}

	if(m_type == FunctionType::ALL) {
		m_all_handle.set_name(name);

		uint32_t solves = m_all_handle.solve(m_functions, m_solves);

		m_all_solves.insert(name, solves);

		return true;
	}

	if(m_type == FunctionType::SOLVE) {

		SolveHandle newFunc(name);

		newFunc.handle_params(params);

		newFunc.solve(m_functions, m_solves);

		m_solves.insert(
			name,
			Pair<std::string, bool>(
				newFunc.get_params(),
				newFunc.get_solve()
			)
		);

		return true;
	}

	body = sh.extract_string_between_cc(fixed_content, '"', '"');

	if(m_type == FunctionType::DEFINE) {
		DefineHandle newFunc(name);

		if(!newFunc.handle_params(params)) {
			return false;
		}

		if(!newFunc.handle_body(body, m_functions)) {
			return false;
		}

		m_functions.insert(
			name,
			Pair<std::string, LogicalTree<std::string>>(
				newFunc.get_params(),
				newFunc.get_function_tree()
			)
		);

		return true;
	}

	return false;
}

const LogicalTree<std::string>& ActionHandle::get_logical_tree(const std::string& function) const {
	return m_functions.get(function).second;
}

const HashMap<Pair<std::string, LogicalTree<std::string>>>& ActionHandle::get_functions() const {
	return m_functions;
}

const HashMap<Pair<std::string, bool>>& ActionHandle::get_solves() const {
	return m_solves;
}

const HashMap<int>& ActionHandle::get_all_solves() const {
	return m_all_solves;
}

bool ActionHandle::handle_type(const std::string &type) {

	if(type[0] != 'D' && type[0] != 'S' && type[0] != 'A' && type[0] != 'F') {
		std::cerr << "[handle_type ERROR] > Unknow function set\n";

		return false;
	}

	if(type == "DEFINE") {
		m_type = FunctionType::DEFINE;
	}
	else if(type == "SOLVE") {
		m_type = FunctionType::SOLVE;
	}
	else if(type == "ALL") {
		m_type = FunctionType::ALL;
	}
	else if(type == "FIND") {
		m_type = FunctionType::FIND;
	}
	else {
		m_type = FunctionType::NONE;

		std::cerr << "[handle_type ERROR] > Unknow function set\n";

		return false;
	}

	return true;
}

bool ActionHandle::handle_name(const std::string &name) {
	StringHandle sh;

	if(sh.contains(name, invalid_symbols)) {
		std::cerr << "[ERROR] Invaid function name set\n";

		return false;
	}

	return true;
}

std::string ActionHandle::remove_white_spaces(const std::string &content) {
	StringHandle sh;

	int idx = 0;

	while(content[idx] == ' ') { idx++; }

	return sh.extract_string_between_ii(content, idx, content.size());
}
