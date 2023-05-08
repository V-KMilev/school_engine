#include "string_handle.h"

#include <iostream>

std::string* StringHandle::split(const std::string &content, const char delimiter) {
	m_substrings.reset_data();

	// Init set count to 1
	int count = 1;

	// Count the number of substrings
	for (const char &c : content) {
		if (c == delimiter) {
			count++;
		}
	}

	// If no delimiters are found return original string
	if(count == 1) {
		m_substrings[0] = content;

		return m_substrings.data();
	}

	// Reset the count so we can use it as index
	count = 0;

	std::string current_substring = "";

	for (const char &c : content) {

		if (c == delimiter) {
			m_substrings.push_back(current_substring);

			current_substring = "";
		} else {

			current_substring += c;
		}
	}

	// Add last substring
	m_substrings.push_back(current_substring);

	return m_substrings.data();
}

std::string* StringHandle::split_limit(const std::string &content, const char delimiter, int to_index) {
	m_substrings.reset_data();

	// Init set count to 1
	int count = 1;

	if(to_index > content.size()) {
		to_index = content.size();
	}

	// Count the number of substrings
	for (int idx = 0; idx <= to_index; idx++) {
		const char &c = content[idx];

		if (c == delimiter) {
			count++;
		}
	}

	// If no delimiters are found return original string
	if(count == 1) {
		m_substrings[0] = content;

		return m_substrings.data();
	}

	// Reset the count so we can use it as index
	count = 0;

	std::string current_substring = "";

	for (int idx = 0; idx < content.size(); idx++) {

		const char &c = content[idx];

		if (c == delimiter && idx <= to_index) {
			if(current_substring.size() == 0) {
				continue;
			}

			m_substrings.push_back(current_substring);

			current_substring = "";
		} else {

			current_substring += c;
		}
	}

	// Add last substring
	m_substrings.push_back(current_substring);

	return m_substrings.data();
}

std::string StringHandle::extract_string_between_cc(const std::string& content, const char start, const char end) const {

	std::string return_sunstring = "";

	for(int idx = 0; idx < content.size(); idx++) {

		if(content[idx] == start) {

			while(content[++idx] != end && idx <= content.size()) {

				return_sunstring += content[idx];
			}

			break;
		}
	}

	return return_sunstring;
}

std::string StringHandle::extract_string_between_ii(const std::string& content, int start, int end) const {

	if(start == end || start > end) {
		return content;
	}

	std::string return_sunstring = "";

	for(int idx = start; idx < end; idx++) {
		return_sunstring += content[idx];
	}

	return return_sunstring;
}

std::string StringHandle::extract_string_between_ic(const std::string& content, int start, const char end) const {

	std::string return_sunstring = "";

	for(int idx = start; content[idx] != end; idx++) {

		return_sunstring += content[idx];
	}

	return return_sunstring;
}

std::string StringHandle::remove_symbol(const std::string &content, const char symbol) const {
	std::string result;

	for (const char &c : content) {

		if (c != symbol) {
			result += c;
		}
	}

	return result;
}

std::string StringHandle::remove_symbol(const std::string &content, const char symbol, int to_index) const {
	std::string result;

	for (int idx = 0; idx <= to_index; idx++) {

		const char &c = content[idx];

		if (c != symbol) {
			result += c;
		}
	}

	return result;
}

std::string StringHandle::remove_all_between(const std::string& content, int start, int end) const {

	if(start == end || start > end) {
		return content;
	}

	std::string return_sunstring = "";

	for(int idx = 0; idx < content.size(); idx++) {
		if(idx < start || idx > end) {
			return_sunstring += content[idx];
		}
	}

	return return_sunstring;
}

bool StringHandle::contains(const std::string &content, const char to_find) const {
	for(const char &c : content) {

		if(c == to_find) {
			return true;
		}
	}

	return false;
}

bool StringHandle::contains(const std::string &content, const std::string &to_find) const {
	for(const char &c : content) {
		for(const char &c_find : to_find) {

			if(c == c_find) {
				return true;
			}
		}
	}

	return false;
}

int StringHandle::get_count(const std::string &content, const char to_find) const {
	int count = 0;

	for(const char &c : content) {

		if(c == to_find) {
			count++;
		}
	}

	return count;
}

int StringHandle::get_count(const std::string &content, const std::string &to_find) const {
	int count = 0;

	for(const char &c : content) {
		for(const char &c_find : to_find) {

			if(c == c_find) {
				count++;
			}
		}
	}

	return count;
}