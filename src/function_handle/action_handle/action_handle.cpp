#include "action_handle.h"

#include <iostream>

#include "string_handle.h"

bool ActionHandle::input_handle(const std::string &content) {
	StringHandle sh;

	StringArray tpye;
	std::string params;
	std::string name;
	std::string body;

	tpye = sh.splitLim(content, ' ', 7, tpye.count);

	name   = sh.extract_string_between(content, ' ', '(');
	params = sh.extract_string_between(content, '(', ')');
	body   = sh.extract_string_between(content, '"', '"');

	if(!set_type(tpye.strings[0])) {
		return false;
	}

	if(!set_name(name)) {
		return false;
	}

	if(!add_function(params, body)) {
		return false;
	}

	return true;
}

bool ActionHandle::set_type(const std::string &type) {

	if(type[0] != 'D' || type[0] != 'S' || type[0] != 'A' || type[0] != 'F') {
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

bool ActionHandle::set_name(const std::string &name) {
	StringHandle sh;

	if((name[0] >= '!' && name[0] <= '@') || (name[0] >= '[' && name[0] <= '~')) {
		std::cerr << "[ERROR] Invaid function name set!\n";

		return false;
	}

	std::string invalid_symbols = "";

	for(char invalid = '!'; invalid <= '@'; invalid++) {
		invalid_symbols += invalid;
	}
	for(char invalid = '['; invalid <= '~'; invalid++) {
		invalid_symbols += invalid;
	}

	if(sh.contains(name, invalid_symbols)) {
		std::cerr << "[ERROR] Invaid function name set!\n";

		return false;
	}

	return true;
}

bool ActionHandle::add_function(const std::string &params, const std::string &body) {


	return true;
}
