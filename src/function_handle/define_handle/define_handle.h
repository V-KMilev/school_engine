#pragma once

#include "hash_map.h"
#include "pair.h"
#include "logical_tree.h"

class DefineHandle {
	public:
		DefineHandle(const std::string &name);
		DefineHandle();

		DefineHandle(const DefineHandle& copy) = delete;
		DefineHandle operator = (const DefineHandle& copy) = delete;

		DefineHandle(DefineHandle && move);
		DefineHandle& operator = (DefineHandle&& move) noexcept;

		~DefineHandle() = default;

		bool handle_body(
			const std::string &body,
			const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions
		);

		bool handle_params(const std::string &params);

		const std::string& get_name() const;

		const std::string& get_params() const;

		const LogicalTree<std::string>& get_function_tree() const;

	private:
		bool single_param(
			const StringHandle& sh,
			const std::string& current_data,
			std::string& clean_data,
			StringArray& clean_body_data
		);

		bool clean_func_param(
			const StringHandle& sh,
			const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
			const std::string& current_data,
			const std::string& clean_data,
			StringArray& clean_body_data,
			HashMap<Pair<std::string, LogicalTree<std::string>>>& fixed_functions
		);

		bool dirty_func_param(
			const StringHandle& sh,
			const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
			const std::string& current_data,
			const std::string& clean_data,
			StringArray& clean_body_data,
			HashMap<Pair<std::string, LogicalTree<std::string>>>& fixed_functions
		);

		Pair<std::string, LogicalTree<std::string>> update_in_func(
			const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions,
			const std::string& func_name,
			const std::string& current_params
		);

	private:
		std::string m_name;
		std::string m_params;

		LogicalTree<std::string> m_function;
};
