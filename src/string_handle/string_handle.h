#pragma once

#include "string_array.h"

class StringHandle {
	public:
		StringHandle() = default;

		~StringHandle() = default;

		std::string* split(const std::string &content, char delimiter);

		std::string* split_limit(const std::string &content, char delimiter, int to_index);

		std::string extract_string_between_cc(const std::string& content, const char start, const char end);

		std::string extract_string_between_ii(const std::string& content, int start, int end);

		std::string extract_string_between_ic(const std::string& content, int start, const char end);

		std::string remove_symbol(const std::string &content, const char symbol);

		std::string remove_symbol(const std::string &content, const char symbol, int to_index);

		std::string remove_all_between(const std::string &content, int start, int end);

		bool contains(const std::string &content, const char to_find);

		bool contains(const std::string &content, const std::string &to_find);

		int get_count(const std::string &content, const char to_find);

		int get_count(const std::string &content, const std::string &to_find);

	private:
		StringArray m_substrings;
};
