#include "string_handle.h"

#include <iostream>

std::string* StringHandle::split(const std::string &content, char delimiter, int &count) {
	// Deallocate any previous substrings
	m_substrings.~StringArray();

	// Init set count to 1
	count = 1;

	// Count the number of substrings
	for (char c : content) {
		if (c == delimiter) {
			count++;
		}
	}

	// Allocate memory for the substrings
	m_substrings.strings = new std::string[count];

	// If no delimiters are found return original string
	if(count == 1) {
		m_substrings.strings[0] = content;

		return m_substrings.strings;
	}

	// Reset the count so we can use it as index
	count = 0;

	std::string current_substring = "";

	for (char c : content) {

		if (c == delimiter) {
			m_substrings.strings[count++] = current_substring;

			current_substring = "";
		} else {

			current_substring += c;
		}
	}

	// Add last substring
	m_substrings.strings[count++] = current_substring;

	return m_substrings.strings;
}

std::string* StringHandle::splitLim(const std::string &content, char delimiter, int to_index, int &count) {
	// Deallocate any previous substrings
	m_substrings.~StringArray();

	// Init set count to 1
	count = 1;

	if(to_index > content.size()) {
		to_index = content.size();
	}

	// Count the number of substrings
	for (int idx = 0; idx < to_index; idx++) {
		char c = content[idx];

		if (c == delimiter) {
			count++;
		}
	}

	// Allocate memory for the substrings
	m_substrings.strings = new std::string[count];

	// If no delimiters are found return original string
	if(count == 1) {
		m_substrings.strings[0] = content;

		return m_substrings.strings;
	}

	// Reset the count so we can use it as index
	count = 0;

	std::string current_substring = "";

	for (int idx = 0; idx < content.size(); idx++) {

		char c = content[idx];

		if (c == delimiter && idx <= to_index) {
			m_substrings.strings[count++] = current_substring;

			current_substring = "";
		} else {

			current_substring += c;
		}
	}

	// Add last substring
	m_substrings.strings[count++] = current_substring;

	return m_substrings.strings;
}

std::string StringHandle::extract_string_between(const std::string& content, const char start, const char end) {

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

std::string StringHandle::remove_symbol(const std::string &content, const char symbol) {
	std::string result;

	for (char c : content) {

		if (c != symbol) {
			result += c;
		}
	}

	return result;
}


bool StringHandle::contains(const std::string &content, const char to_find) {
	for(char c : content) {

		if(c == to_find) {
			return true;
		}
	}

	return false;
}

bool StringHandle::contains(const std::string &content, const std::string &to_find) {
	for(char c : content) {
		for(char c_find : to_find) {

			if(c == c_find) {
				return true;
			}
		}
	}

	return false;
}
