#pragma once

#include "string_array.h"

class StringHandle {
	public:
		StringHandle() = default;

		~StringHandle() = default;

		std::string* split(const std::string &content, char delimiter, int &count);

		std::string extract_string_between(const std::string& content, const char start, const char end);

	private:
		StringArray m_substrings;
};
