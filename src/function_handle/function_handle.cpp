#include "function_handle.h"

const std::string& FunctionHandle::get_name() const {
	return m_name;
}

const LogicalTree<std::string>& FunctionHandle::get_function_tree() const {
	return m_function;
}
