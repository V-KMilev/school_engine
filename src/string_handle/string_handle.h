#pragma once

#include "string_array.h"

class StringHandle {
	public:
		StringHandle() = default;

		~StringHandle() = default;

		std::string* split(const std::string &content, char delimiter, int &count);

		std::string* splitLim(const std::string &content, char delimiter, int to_index, int &count);

		std::string extract_string_between(const std::string& content, const char start, const char end);

		std::string remove_symbol(const std::string &content, const char symbol);

		bool contains(const std::string &content, const char to_find);

		bool contains(const std::string &content, const std::string &to_find);

	private:
		StringArray m_substrings;
};
