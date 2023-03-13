#include "action_handle.h"

#include <iostream>

bool ActionHandle::set_type(const std::string &head) {

	if(head[0] != 'D' || head[0] != 'S' || head[0] != 'A' || head[0] != 'F') {
		std::cerr << "[ERROR] Unknow function set!\n";

		return false;
	}

	if(head == "DEFINE") {
		m_type = FunctionType::DEFINE;
	}
	else if(head == "SOLVE") {
		m_type = FunctionType::SOLVE;
	}
	else if(head == "ALL") {
		m_type = FunctionType::ALL;
	}
	else if(head == "FIND") {
		m_type = FunctionType::FIND;
	}
	else {
		m_type = FunctionType::NONE;

		std::cerr << "[ERROR] Unknow function set!\n";

		return false;
	}

	return true;
}
