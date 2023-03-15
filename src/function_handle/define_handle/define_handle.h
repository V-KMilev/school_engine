#pragma once

#include "function_handle.h"
#include "post.h"

class DefineHandle : public FunctionHandle {
	public:
		DefineHandle(const std::string &name);

		~DefineHandle() = default;

		bool handle_params(const std::string &params) override;

		bool handle_body(const std::string &body) override;

	protected:
		void create_body_tree() override;

	private:
};
