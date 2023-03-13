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

	// TODO: Find a solution to this problem ;)
	m_parameters.count = 3;

	std::string* temp = sh.split(params, ',', m_parameters.count);

	m_parameters.strings = new std::string[m_parameters.count];

	m_parameters = temp;
}

bool DefineHandle::set_body_tree() {
	return true;
}
