#pragma once

#include <string>

struct myStringPtr {
	public:
		myStringPtr& operator = (const std::string* str) {

			for(int idx = 0; idx < count; idx++) {

				strings[idx] = str[idx];
			}

			return *this;
		}

	public:
		std::string* strings = nullptr;
		int count = 0;
};
