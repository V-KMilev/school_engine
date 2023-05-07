#include "action_handle.h"

#include <iostream>

#include "string_handle.h"
#include "post.h"

bool ActionHandle::handle_input(const std::string &content) {
	StringHandle sh;

	StringArray tpye;

	std::string params;
	std::string name;
	std::string body;

	std::string fixed_content = remove_white_spaces(content);

	tpye = sh.split_limit(fixed_content, ' ', 6);

	if(!handle_type(tpye.data()[0])) {
		return false;
	}

	fixed_content = remove_white_spaces(tpye.data()[1]);

	name   = sh.extract_string_between_ic(fixed_content, 0, '(');
	params = sh.extract_string_between_cc(fixed_content, '(', ')');
	body   = sh.extract_string_between_cc(fixed_content, '"', '"');

	if(!handle_name(name)) {
		return false;
	}

	if(!add_function(name, params, body)) {
		return false;
	}

	return true;
}

bool ActionHandle::handle_type(const std::string &type) {

	if(type[0] != 'D' && type[0] != 'S' && type[0] != 'A' && type[0] != 'F') {
		std::cerr << "[ERROR] Unknow function set!\n";

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

		std::cerr << "[ERROR] Unknow function set!\n";

		return false;
	}

	return true;
}

bool ActionHandle::handle_name(const std::string &name) {
	StringHandle sh;

	if((name[0] >= '!' && name[0] <= '@') ||
		(name[0] >= '[' && name[0] <= '`') ||
		(name[0] >= '{' && name[0] <= '~')
	) {
		std::cerr << "[ERROR] Invaid function name set!\n";

		return false;
	}

	if(sh.contains(name, invalid_symbols)) {
		std::cerr << "[ERROR] Invaid function name set!\n";

		return false;
	}

	return true;
}

bool ActionHandle::add_function(const std::string &name, const std::string &params, const std::string &body) {

	DefineHandle newFunc(name);

	if(!newFunc.handle_params(params)) {
		return false;
	}

	if(!newFunc.handle_body(body, m_cached_funcs)) {
		return false;
	}

	m_cached_funcs.insert(
		name,
		Pair<std::string, LogicalTree<std::string>>(
			newFunc.get_in_order(),
			newFunc.get_function_tree()
		)
	);

	return true;
}

std::string ActionHandle::remove_white_spaces(const std::string &content) {
	StringHandle sh;

	int idx = 0;

	while(content[idx] == ' ') { idx++; }

	return sh.extract_string_between_ii(content, idx, content.size());
}
