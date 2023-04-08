#pragma once

#include "function_handle.h"
#include "post.h"

class DefineHandle : public FunctionHandle {
	public:
		DefineHandle(const std::string &name);
		DefineHandle();

		DefineHandle(const DefineHandle& copy) = delete;
		DefineHandle operator = (const DefineHandle& copy) = delete;

		DefineHandle(DefineHandle && move);
		DefineHandle& operator = (DefineHandle&& move) noexcept;

		~DefineHandle() = default;

		bool handle_params(const std::string &params) override;

		bool handle_body(const std::string &body) override;

	private:
};
