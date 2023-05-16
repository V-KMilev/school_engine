#pragma once

#include <string>

#include "hash_map.h"
#include "pair.h"
#include "logical_tree.h"

class SolveHandle {
	public:
		SolveHandle();

		SolveHandle(const std::string& name);

		bool handle_params(const std::string &params);

		const std::string& name() const;

		const std::string& params() const;

		bool solve() const;

		void name(const std::string& name);

		void params(const std::string& params);

		void solve(
			const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
			const HashMap<Pair<std::string, bool>>& solves
		);

	private:
		std::string m_name;
		std::string m_params;

		bool m_solve;
};
