#pragma once

#include "string_array.h"

class StringHandle {
	public:
		StringHandle() = default;

		~StringHandle() = default;

		std::string* split(const std::string &content, const char delimiter);

		std::string* split_limit(const std::string &content, const char delimiter, int to_index);

		std::string extract_string_between_cc(const std::string& content, const char start, const char end) const;

		std::string extract_string_between_ii(const std::string& content, int start, int end) const;

		std::string extract_string_between_ic(const std::string& content, int start, const char end) const;

		std::string remove_symbol(const std::string &content, const char symbol) const;

		std::string remove_symbol(const std::string &content, const char symbol, int to_index) const;

		std::string remove_all_between(const std::string &content, int start, int end) const;

		bool contains(const std::string &content, const char to_find) const;

		bool contains(const std::string &content, const std::string &to_find) const;

		int get_count(const std::string &content, const char to_find) const;

		int get_count(const std::string &content, const std::string &to_find) const;

		int precedence(const std::string& str);

		StringArray convert_to_postfix(const StringArray& body);

	private:
		StringArray m_substrings;
};
