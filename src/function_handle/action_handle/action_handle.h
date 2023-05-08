#pragma once

#include <string>

#include "hash_map.h"
#include "pair.h"
#include "logical_tree.h"

enum class FunctionType {
	NONE   = 0,
	DEFINE = 1,
	SOLVE  = 2,
	ALL    = 3,
	FIND   = 4
};

class ActionHandle {
	public:
		ActionHandle() = default;

		~ActionHandle() = default;

		bool handle_input(const std::string &content);

		const LogicalTree<std::string>& get_logical_tree(const std::string& function) const;

		const bool& get_solve(const std::string& function) const;

	private:
		bool handle_type(const std::string &type);

		bool handle_name(const std::string &name);

		std::string remove_white_spaces(const std::string &content);

	private:
		FunctionType m_type;

		HashMap<Pair<std::string, LogicalTree<std::string>>> m_functions;
		HashMap<bool> m_solves;
};
