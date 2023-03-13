#pragma once

#include <string>

#include "function_handle.h"

enum class FunctionType {
	NONE   = 0,
	DEFINE = 1,
	SOLVE  = 2,
	ALL    = 3,
	FIND   = 4
};

class ActionHandle {
	public:
		ActionHandle();

		~ActionHandle();

		bool set_type(const std::string &head);

		bool add_handle();

	private:
		std::string m_head;
		FunctionType m_type;

		FunctionHandle* m_functions;
};
