#pragma once

#include "tree.h"
#include "string_array.h"

class FunctionHandle {
	public:
		FunctionHandle(const std::string &name, const std::string &body) : m_name(name), m_body(body) {}

		~FunctionHandle() = default;

		virtual bool set_body_tree() = 0;

	protected:
		std::string m_name;
		std::string m_body;

		StringArray m_cached_params;

		Tree m_function;
};
