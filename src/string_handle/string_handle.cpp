#include "string_handle.h"

#include <iostream>

#include "string_array.h"
#include "stack.h"

static StringArray data;

namespace StringHandle {
	std::string* split(const std::string &content, const char delimiter) {
		data.reset_data();

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
			data.push_back(content);

			return data.data();
		}

		// Reset the count so we can use it as index
		count = 0;

		std::string current_substring = "";

		for (const char &c : content) {

			if (c == delimiter) {
				data.push_back(current_substring);

				current_substring = "";
			} else {

				current_substring += c;
			}
		}

		// Add last substring
		data.push_back(current_substring);

		return data.data();
	}

	std::string* split_limit(const std::string &content, const char delimiter, int to_index) {
		data.reset_data();

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
			data.push_back(content);

			return data.data();
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

				data.push_back(current_substring);

				current_substring = "";
			} else {

				current_substring += c;
			}
		}

		// Add last substring
		data.push_back(current_substring);

		return data.data();
	}

	std::string extract_string_between_cc(const std::string& content, const char start, const char end) {

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

	std::string extract_string_between_ii(const std::string& content, int start, int end) {

		if(start == end || start > end) {
			return content;
		}

		std::string return_sunstring = "";

		for(int idx = start; idx < end; idx++) {
			return_sunstring += content[idx];
		}

		return return_sunstring;
	}

	std::string extract_string_between_ic(const std::string& content, int start, const char end) {

		std::string return_sunstring = "";

		for(int idx = start; content[idx] != end; idx++) {

			return_sunstring += content[idx];
		}

		return return_sunstring;
	}

	std::string remove_symbol(const std::string &content, const char symbol) {
		std::string result;

		for (const char &c : content) {

			if (c != symbol) {
				result += c;
			}
		}

		return result;
	}

	std::string remove_symbol(const std::string &content, const char symbol, int to_index) {
		std::string result;

		for (int idx = 0; idx <= to_index; idx++) {

			const char &c = content[idx];

			if (c != symbol) {
				result += c;
			}
		}

		return result;
	}

	std::string remove_all_between(const std::string& content, int start, int end) {

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

	bool contains(const std::string &content, const char to_find) {
		for(const char &c : content) {

			if(c == to_find) {
				return true;
			}
		}

		return false;
	}

	bool contains(const std::string &content, const std::string &to_find) {
		for(const char &c : content) {
			for(const char &c_find : to_find) {

				if(c == c_find) {
					return true;
				}
			}
		}

		return false;
	}

	int count(const std::string &content, const char to_find) {
		int count = 0;

		for(const char &c : content) {

			if(c == to_find) {
				count++;
			}
		}

		return count;
	}

	int count(const std::string &content, const std::string &to_find) {
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

	int precedence(const std::string& str) {
		if(str == "&") {
			return 2;
		}
		if(str == "|") {
			return 1;
		}

		return 0;
	}

	StringArray convert_to_postfix(const StringArray& body) {
		data.reset_data();

		Stack<std::string> st;

		for (int idx = 0; idx < body.count(); idx++) {
			const std::string& str = body.data()[idx];

			if(str.size() > 1) {
				data.push_back(str);
			}

			else if (str == "&" || str == "|") {
				while (!st.empty() && precedence(st.top()) >= precedence(str)) {
					data.push_back(st.pop());
				}

				st.push(str);
			}

			else if (str == "(") {
				st.push(str);
			}

			else if (str == ")") {
				while (!st.empty() && st.top() != "(") {
					data.push_back(st.pop());
				}

				st.pop();
			}
			else if(str.size() == 1) {
				data.push_back(str);
			}
			else {
				std::cerr << "[convert_to_postfix ERROR] > Unexpected error\n";
				exit(-1);
			}
		}

		while (!st.empty()) {
			data.push_back(st.pop());
		}

		return data;
	}

	int to_int(const std::string& content) {
		int result = 0;

		for(const char& c : content) {
			if (c >= '0' && c <= '9') {
				result = result * 10 + (c - '0');
			}
		}

		return result;
	}
};
