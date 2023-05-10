#pragma once

#include <string>

#include "hash_map.h"
#include "pair.h"
#include "logical_tree.h"

class AllHandle {
	public:
		AllHandle();

		AllHandle(const std::string& name);

		void set_name(const std::string& name);

		uint32_t solve(
			const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
			HashMap<Pair<std::string, bool>>& solves
		);

	private:
		void find_all(
			const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
			HashMap<Pair<std::string, bool>>& solves
		);

	private:
		std::string m_name;

		uint32_t m_solves;
};
