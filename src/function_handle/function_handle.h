#pragma once

#include "tree.h"
#include "string_array.h"

class FunctionHandle {
	public:
		FunctionHandle(const std::string &name);

		~FunctionHandle() = default;

		virtual bool handle_params(const std::string &params) = 0;

		virtual bool handle_body(const std::string &body) = 0;

	protected:
		virtual void create_body_tree() = 0;

	protected:
		std::string m_name;

		StringArray m_cached_params;

		Tree m_function;
};
