#pragma once

#include "logical_tree.h"
#include "string_array.h"

#include "hash_map.h"

class FunctionHandle {
	public:
		FunctionHandle() = default;
		~FunctionHandle() = default;

		const std::string& get_name() const;

		const LogicalTree<std::string>& get_function_tree() const;

	protected:
		std::string m_name;

		StringArray m_cached_params;

		LogicalTree<std::string> m_function;
};
