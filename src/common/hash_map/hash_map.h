#pragma once

#include <string>

#include "error_handle.h"

template<typename T>
struct HashNode {
	public:
		std::string key;
		T value;
		HashNode<T>* next;
};

template<typename T>
class HashMap {
	public:
		HashMap();

		~HashMap();

		void insert(const std::string& key, const T& value);

		void remove(const std::string& key);

		const T& get(const std::string& key) const;

		int get_size() const;

	private:
		int hash(const std::string& key) const;

		void resize(int new_size);

	private:
		HashNode<T>** m_map;

		int m_element_count;
		// Default size: 11
		int m_size;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* .cpp part */

template<typename T>
HashMap<T>::HashMap() : m_size(11), m_element_count(0) {

	m_map = new HashNode<T>*[m_size];

	// Set all to nullptr
	for (int idx = 0; idx < m_size; idx++) {
		m_map[idx] = nullptr;
	}
}

template<typename T>
HashMap<T>::~HashMap() {
	for (int idx = 0; idx < m_size; idx++) {

		while(m_map[idx] != nullptr) {

			HashNode<T>* temp = m_map[idx];
			m_map[idx] = m_map[idx]->next;

			delete temp;
		}
	}

	// Delete the array
	delete[] m_map;
}

template<typename T>
void HashMap<T>::insert(const std::string& key, const T& value) {
	// Get index based on the hash value
	int index = hash(key);

	// Check if the key already exists
	HashNode<T>* current = m_map[index];

	// Continue until there are no more nodes
	while (current != nullptr) {

		if (current->key == key) {
			// Set current's value to new value
			current->value = value;
			return;
		}
		current = current->next;
	}

	// Create a new HashNode and insert it into the hash map
	HashNode<T>* new_node = new HashNode<T>{key, value, nullptr};

	// Set new_node to point to the last added HashNode
	new_node->next = m_map[index];

	// Set new_node as last added HashNode
	m_map[index] = new_node;

	// Increse element count
	m_element_count++;

	// Resize the map if it's more than 70% full
	if (m_element_count > m_size * 0.7f) {
		resize(2 * m_size);
	}
}

template<typename T>
void HashMap<T>::remove(const std::string& key) {
	// Get the index based on the hash value
	int index = hash(key);

	// Search for the key in the linked list at the given index
	HashNode<T>* current = m_map[index];
	HashNode<T>* prev = nullptr;

	while (current != nullptr) {
		if (current->key == key) {
			// Remove the node from the linked list
			if (prev == nullptr) {
				// Current node is the head of the linked list
				m_map[index] = current->next;
			} else {
				// Current node is not the head of the linked list
				prev->next = current->next;
			}
			
			// Delete the removed node
			delete current;
			
			// Decrease the element count
			m_element_count--;
			
			return;
		}
		
		prev = current;
		current = current->next;
	}

	// Key not found in the hash map
	return;
}

template<typename T>
const T& HashMap<T>::get(const std::string& key) const {
	// Get index based on the hash value
	int index = hash(key);

	// Search for the key in the linked list at the given index
	HashNode<T>* current = m_map[index];

	while (current != nullptr) {

		if (current->key == key) {

			// Return the value if the key is found
			return current->value;
		}
		current = current->next;
	}

	// Return a default-constructed value if the key is not found
	static T default_value;
	return default_value;
}

template<typename T>
int HashMap<T>::get_size() const {
	return m_size;
}

template<typename T>
int HashMap<T>::hash(const std::string& key) const {
	// "Polynomial rolling hash" algorithm
	int hash_value = 0;

	for (const char &c : key) {
		hash_value = ((hash_value << 5) + c) % m_size;
	}

	return hash_value;
}

template<typename T>
void HashMap<T>::resize(int new_size) {
	// Check if new size is logical
	if (new_size <= m_size) {
		return;
	}

	// New map with the new size
	HashNode<T>** new_map = new HashNode<T>*[new_size];

	// Set all to nullptr
	for (int i = 0; i < new_size; i++) {
		new_map[i] = nullptr;
	}

	// Update the size
	m_size = new_size;

	// Rehash all existing key-value pairs into the new map
	for (int i = 0; i < m_size / 2; i++) {

		HashNode<T>* node = m_map[i];

		while(node != nullptr) {
			// Compute the new index for the current HashNode.
			int index = hash(node->key);

			// Insert the current HashNode at the head of the corresponding list in the new array.
			HashNode<T>* next = node->next;

			node->next = new_map[index];

			new_map[index] = node;

			node = next;
		}
	}

	// Update the hash map
	delete[] m_map;

	m_map = new_map;
}
