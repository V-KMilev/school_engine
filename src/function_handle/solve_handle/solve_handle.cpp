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
		std::cerr << "[ERROR] Invaid parameter(s) set\n";
		return false;
	}

	if(sh.contains(m_params, "23456789")) {
		std::cerr << "[ERROR] Invaid parameter(s) set\n";
		return false;
	}

	return true;
}

const std::string& SolveHandle::name() const {
	return m_name;
}

const std::string& SolveHandle::params() const {
	return m_params;
}

bool SolveHandle::solve() const {
	return m_solve;
}

void SolveHandle::name(const std::string& name) {
	m_name = name;
}

void SolveHandle::params(const std::string& params) {
	m_params = params;
}

void SolveHandle::solve(
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	const HashMap<Pair<std::string, bool>>& solves
) {
	const Pair<std::string, LogicalTree<std::string>>& func = functions.get(m_name);
	const Pair<std::string, bool>& solve = solves.get(m_name);

	const std::string& func_params = func.first;

	if(m_params.size() != func_params.size()) {
		std::cerr << "[solve ERROR] > Miss set of parameter(s)\n";
		exit(-1);
	}

	std::string copy = m_params;

	// Aka size * 2
	m_params.resize(m_params.size() + m_params.size());

	for(int idx = 0; idx < func_params.size(); idx++) {
		m_params[2 * idx + 0] = func_params[idx];
		m_params[2 * idx + 1] = copy[idx];
	}

	if(solve != Pair<std::string, bool>()) {
		if(m_params == solve.first) {
			m_solve = solve.second;
			return;
		}
	}

	m_solve = func.second.solve(m_params);
}
