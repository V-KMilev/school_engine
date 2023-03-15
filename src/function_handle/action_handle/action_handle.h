#pragma once

#include <string>

#include "function_handle.h"

#include "define_handle.h"

#include "hash_map.h"

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

	private:
		bool handle_type(const std::string &tpye);

		bool handle_name(const std::string &name);

		bool add_function(const std::string &name, const std::string &params, const std::string &body);

	private:
		FunctionType m_type;

		HashMap<DefineHandle> m_cached_funcs;
};
