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

		const std::string& get_name() const;

		const std::string& get_params() const;

		bool get_solve() const;

		void set_name(const std::string& name);

		void set_params(const std::string& params);

		void solve(
			const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
			const HashMap<Pair<std::string, bool>>& solves
		);

	private:
		std::string m_name;
		std::string m_params;

		bool m_solve;
};
