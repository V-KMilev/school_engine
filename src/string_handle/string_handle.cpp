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

std::string StringHandle::extract_string_between(const std::string& content, const char start, const char end) {

	std::string return_sunstring = "";

	for(int idx = 0; idx < content.size(); idx++) {

		if(content[idx] == start) {

			while(content[idx+1] != end && idx+1 != content.size()) {

				return_sunstring += content[++idx];
			}
		}
	}

	return return_sunstring;
}