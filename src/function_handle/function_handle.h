#pragma once

#include "stringptr.h"

#include "tree.h"

class FunctionHandle {
	public:
		FunctionHandle(const std::string &name, const std::string &body) : m_name(name), m_body(body) {}

		virtual ~FunctionHandle() {
			delete[] m_parameters.strings;
		}

		virtual bool set_body_tree() = 0;

	protected:
		std::string m_name;
		std::string m_body;

		myStringPtr m_parameters;

		Tree m_function;
};
