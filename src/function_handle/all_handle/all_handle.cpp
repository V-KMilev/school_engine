#include "all_handle.h"

#include "solve_handle.h"

AllHandle::AllHandle() : m_solves(0), m_name("") {}

AllHandle::AllHandle(const std::string& name) : m_solves(0), m_name(name) {}

void AllHandle::set_name(const std::string& name) {
	m_name = name;
}

uint32_t AllHandle::solve(
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	HashMap<Pair<std::string, bool>>& solves
) {
	find_all(functions, solves);

	return m_solves;
}

void AllHandle::find_all(
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
	HashMap<Pair<std::string, bool>>& solves
) {
	const Pair<std::string, LogicalTree<std::string>>& func = functions.get(m_name);
	const Pair<std::string, bool>& solve = solves.get(m_name);

	uint32_t count = func.first.size();

	if(count <= 0) {
		std::cerr << "[find_all ERROR] > Unknow function set\n";
		return;
	}

	bool ignore_solves = true;

	if(solve != Pair<std::string, bool>()) {
		ignore_solves = false;
	}

	SolveHandle solver(m_name);

	std::string params(count, '0');

	for(uint32_t idx = 0; idx < (1 << count); idx++) {
		for(uint32_t var = 0; var < count; var++) {

			if(((idx >> var) & 1) == 1) {
				params[count - var - 1] = '1';
				continue;
			}

			params[count - var - 1] = '0';
		}

		if(!ignore_solves && solve.first == params) {
			solves.insert(m_name + "-" + params, Pair<std::string, bool>(params, solve.second));

			m_solves |= (1 << idx);
			continue;
		}

		solver.set_params(params);

		solver.solve(functions, solves);

		if(solver.get_solve() == 1) {
			m_solves |= (1 << idx);
		}

		solves.insert(m_name + "-" + params, Pair<std::string, bool>(params, solver.get_solve()));
	}
}
