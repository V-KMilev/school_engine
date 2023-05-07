#include "function_handle.h"

const std::string& FunctionHandle::get_name() const {
	return m_name;
}

const std::string& FunctionHandle::get_in_order() const {
	return m_in_order;
}

const LogicalTree<std::string>& FunctionHandle::get_function_tree() const {
	return m_function;
}
