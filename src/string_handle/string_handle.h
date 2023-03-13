#pragma once

#include "stringptr.h"

class StringHandle {
	public:
		StringHandle();

		~StringHandle();

		std::string* split(const std::string &content, char delimiter, int &count);

		std::string extract_string_between(const std::string& content, const char start, const char end);

	private:
		myStringPtr m_substrings;
};
