#include "define_handle.h"

#include <iostream>
#include <string.h>

#include "string_handle.h"


DefineHandle::DefineHandle(
	const std::string &name,
	const std::string &body
)
 : FunctionHandle(name, body)
{
	// Set parameters
	StringHandle sh;

	std::string params = "";
	params = sh.extract_string_between(m_name, '(', ')');

	m_cached_params = sh.split(params, ',', m_cached_params.count);
}

bool DefineHandle::set_body_tree() {
	return true;
}
