#include "string_array.h"

StringArray::StringArray(std::string* string_ptr) : m_size(11), m_count(0) {
	while (string_ptr[m_count] != "") {
		m_count++;
	}

	m_size = m_count * 2;

	// Allocate mem for the new copy
	m_data = new std::string[m_size];

	// Copy the strings
	for(int idx = 0; idx < m_count; idx++) {
		m_data[idx] = string_ptr[idx];
	}
}

StringArray::StringArray(int size) : m_size(size), m_count(0) {
	m_data = new std::string[size];
}

StringArray::StringArray() : m_size(11), m_count(0) {
	m_data = new std::string[m_size];
}

StringArray::~StringArray() {
	if(m_data != nullptr) {

		delete[] m_data;

		m_data = nullptr;
	}
}

std::string& StringArray::operator[](int index) {
	return m_data[index];
}

StringArray& StringArray::operator = (std::string* string_ptr) {
	// Deallocate any previous strings
	if (m_data != nullptr) {

		delete[] m_data;

		m_data = nullptr;
	}

	// Determine the new count
	m_count = 0;

	while (string_ptr[m_count] != "") {
		m_count++;
	}

	m_size = m_count * 2;

	m_data = new std::string[m_size];

	for(int idx = 0; idx < m_count; idx++) {
		m_data[idx] = string_ptr[idx];
	}

	return *this;
}

void StringArray::reset_data() {
	for(int idx = 0; idx < m_size; idx++) {
		m_data[idx] = "";
	}
}

void StringArray::push_back(const std::string& str) {
	// Resize the array if it's more than 70% full
	if (m_count + 1 > m_size * 0.7) {
		resize(m_size * 2);
	}
	m_data[m_count++] = str;
}

void StringArray::push_back(const char& c) {
	// Resize the array if it's more than 70% full
	if (m_count + 1 > m_size * 0.7) {
		resize(m_size * 2);
	}
	m_data[m_count++] = c;
}

const std::string* StringArray::data() const { return m_data; }

std::string* StringArray::data() { return m_data; }

int StringArray::size() const { return m_size; }

int StringArray::count() const { return m_count; }

int& StringArray::count() { return m_count; }

void StringArray::resize(int size) {
	std::string* new_data = new std::string[size];

	for (int i = 0; i < m_size; i++) {
		new_data[i] = m_data[i];
	}

	delete[] m_data;
	m_data = new_data;
	m_size = size;
}