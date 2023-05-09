#pragma once

#include <string>

class StringArray {
	public:
		StringArray(std::string* string_ptr);
		StringArray(int size);
		StringArray();

		~StringArray();

		std::string& operator[](int index);

		StringArray& operator = (std::string* string_ptr);

		void reset_data();

		void push_back(const std::string& str);
		void push_back(const char& c);

		const std::string* data() const;

		std::string* data();

		int size() const;

		int count() const;

		int& count();

	private:
		void resize(int size);

	private:
		std::string* m_data;
		// Default size: 11
		int m_size;
		int m_count;
};
