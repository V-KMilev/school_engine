#pragma once

#include "string_array.h"

namespace StringHandle {
	extern std::string* split(const std::string &content, const char delimiter);

	extern std::string* split_limit(const std::string &content, const char delimiter, int to_index);

	extern std::string extract_string_between_cc(const std::string& content, const char start, const char end);

	extern std::string extract_string_between_ii(const std::string& content, int start, int end);

	extern std::string extract_string_between_ic(const std::string& content, int start, const char end);

	extern std::string remove_symbol(const std::string &content, const char symbol);

	extern std::string remove_symbol(const std::string &content, const char symbol, int to_index);

	extern std::string remove_all_between(const std::string &content, int start, int end);

	extern bool contains(const std::string &content, const char to_find);

	extern bool contains(const std::string &content, const std::string &to_find);

	extern int count(const std::string &content, const char to_find);

	extern int count(const std::string &content, const std::string &to_find);

	extern int precedence(const std::string& content);

	extern StringArray convert_to_postfix(const StringArray& body);

	extern int to_int(const std::string& content);
};
