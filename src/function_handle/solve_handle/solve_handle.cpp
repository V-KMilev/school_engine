#include "solve_handle.h"

#include <iostream>

#include "string_handle.h"
#include "post.h"

SolveHandle::SolveHandle() : m_name(""), m_params(""), m_solve(false) {}

SolveHandle::SolveHandle(const std::string& name) : m_name(name), m_params(""), m_solve(false) {}

bool SolveHandle::handle_params(const std::string &params) {
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

const std::string& SolveHandle::get_name() const {
	return m_name;
}

const std::string& SolveHandle::get_params() const {
	return m_params;
}

bool SolveHandle::get_solve() const {
	return m_solve;
}

void SolveHandle::solve(const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions) {
	const Pair<std::string, LogicalTree<std::string>>& func = functions.get(m_name);

	const std::string& func_params = func.first;

	if(m_params.size() != func_params.size()) {
		std::cerr << "[solve ERROR] > Miss set of parameters!\n";
		exit(-1);
	}

	std::string copy = m_params;

	// Aka size * 2
	m_params.resize(m_params.size() + m_params.size());

	for(int idx = 0; idx < func_params.size(); idx++) {
		m_params[2 * idx + 0] = func_params[idx];
		m_params[2 * idx + 1] = copy[idx];
	}

	m_solve = func.second.solve(m_params);
}
