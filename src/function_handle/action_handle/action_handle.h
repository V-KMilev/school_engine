#pragma once

#include <string>

#include "function_handle.h"

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

		bool input_handle(const std::string &content);

	private:
		bool set_type(const std::string &tpye);

		bool set_name(const std::string &name);

		bool add_function(const std::string &params, const std::string &body);

	private:
		FunctionType m_type;
		std::string m_name;

		HashMap<FunctionHandle*> m_cached_funcs;
};
