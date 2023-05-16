#pragma once

#include <string>

class StringArray {
	public:
		StringArray(std::string* array);
		StringArray(int size);
		StringArray();

		StringArray(const StringArray& copy);

		~StringArray();

		std::string& operator[](int index);

		StringArray& operator = (std::string* array);

		StringArray& operator = (const StringArray& copy);

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
