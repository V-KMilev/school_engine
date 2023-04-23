#include "define_handle.h"

#include <iostream>
#include <string>

#include "string_handle.h"

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

	m_function.set_body(body);
	m_function.build();

	m_function.print();

	return true;
}
