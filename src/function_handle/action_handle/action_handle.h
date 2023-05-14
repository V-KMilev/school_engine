#pragma once

#include <string>

#include "hash_map.h"
#include "pair.h"
#include "logical_tree.h"

#include "all_handle.h"

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

		const HashMap<Pair<std::string, LogicalTree<std::string>>>& get_functions() const;

		const HashMap<Pair<std::string, bool>>& get_solves() const;

		const HashMap<int>& get_all_solves() const;

	private:
		bool handle_type(const std::string &type);

		bool handle_name(const std::string &name);

		std::string remove_white_spaces(const std::string &content);

	public:
		FunctionType m_type;

		HashMap<Pair<std::string, LogicalTree<std::string>>> m_functions;
		HashMap<Pair<std::string, bool>> m_solves;
		HashMap<int> m_all_solves;

		AllHandle m_all_handle;
};
