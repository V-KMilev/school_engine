#pragma once

#include "logical_tree.h"
#include "string_array.h"

class FunctionHandle {
	public:
		FunctionHandle() = default;
		~FunctionHandle() = default;

		virtual bool handle_params(const std::string &params) = 0;

		virtual bool handle_body(const std::string &body) = 0;

	protected:
		std::string m_name;

		StringArray m_cached_params;

		LogicalTree m_function;
};
