#include "define_handle.h"

#include <iostream>
#include <string>

#include "string_handle.h"

DefineHandle::DefineHandle(const std::string &name) : FunctionHandle(name) {}

bool DefineHandle::handle_params(const std::string &params) {
	StringHandle sh;

	m_cached_params = sh.split(params, ',', m_cached_params.count);

	for(int idx = 0; idx < m_cached_params.count; idx++) {

		std::string& param = m_cached_params.strings[idx];

		if((param[0] >= '!' && param[0] <= '@') ||
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

bool DefineHandle::handle_body(const std::string &body) {

	create_body_tree();

	return true;
}

void DefineHandle::create_body_tree() {

}
