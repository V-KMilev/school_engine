#pragma once

#include "function_handle.h"

class DefineHandle : public FunctionHandle {
	public:
		DefineHandle(const std::string &name, const std::string &body);

		~DefineHandle() = default;

		bool set_body_tree() override;

	private:
};
