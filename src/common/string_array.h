#pragma once

#include <string>

struct StringArray {
	public:
		StringArray() : strings(nullptr), count(0) {}

		~StringArray() {
			delete[] strings;
			count = 0;
		}

		StringArray& operator = (const std::string* content) {
			// Deallocate any previous strings
			delete[] strings;

			// Aallocate mem for the new copy
			strings = new std::string[count];

			for(int idx = 0; idx < count; idx++) {

				strings[idx] = content[idx];
			}

			return *this;
		}

	public:
		std::string* strings;
		int count;
};
