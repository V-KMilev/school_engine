#pragma once

#include <string>

#include "error_handle.h"

template<typename T>
struct Node {
	std::string key;
	T value;

	// Next node ptr
	Node* next;
};

template<typename T>
class HashMap {
	public:
		HashMap();

		~HashMap();

		void insert(const std::string& key, T value);

		T get(const std::string& key) const;

	private:
		int hash(const std::string& key) const;

		void resize(int new_size);

	private:
		Node<T>** m_map;

		int m_element_count;
		// Default size: 10
		int m_size;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* .cpp part */

template<typename T>
HashMap<T>::HashMap() : m_size(10), m_element_count(0) {

	m_map = new Node<T>*[m_size];

	// Set all to nullptr
	for (int i = 0; i < m_size; i++) {
		m_map[i] = nullptr;
	}
}

template<typename T>
HashMap<T>::~HashMap() {
	// Delete all nodes in the hash map
	for (int i = 0; i < m_size; i++) {

		Node<T>* node = m_map[i];

		while (node) {
			// Get next node before deleting the current
			Node<T>* next = node->next;

			delete node;

			node = next;
		}
	}

	// Delete the array of pointers to nodes
	delete[] m_map;
}

template<typename T>
void HashMap<T>::insert(const std::string& key, T value) {
	// Get index based on the hash value
	int index = hash(key) % m_size;

	// Check if the key already exists
	Node<T>* current = m_map[index];

	// Continue until there are no more nodes
	while (current != nullptr) {

		if (current->key == key) {
			// Set current's value to new value
			current->value = value;
			return;
		}
		current = current->next;
	}

	// Create a new node and insert it into the hash map
	Node<T>* new_node = new Node<T>{key, value, nullptr};

	// Set new_node to point to the last added node
	new_node->next = m_map[index];

	// Set new_node as last added node
	m_map[index] = new_node;

	// Increse element count
	m_element_count++;

	// Resize the map if it's more than 70% full
	if (m_element_count > m_size * 0.7f) {
		resize(2 * m_size);
	}
}

template<typename T>
T HashMap<T>::get(const std::string& key) const {
	// Get index based on the hash value
	int index = hash(key) % m_size;

	// Search for the key in the linked list at the given index
	Node<T>* current = m_map[index];

	while (current != nullptr) {

		if (current->key == key) {

			// Return the value if the key is found
			return current->value;
		}
		current = current->next;
	}

	// Return a default-constructed value if the key is not found
	return T();
}

template<typename T>
int HashMap<T>::hash(const std::string& key) const {
	// "Polynomial rolling hash" algorithm
	int hash_value = 0;

	for (char c : key) {
		// 37 becouse its my favorit number :)
		hash_value += (hash_value * 37 + c) % m_size;
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
	Node<T>** new_map = new Node<T>*[new_size];

	// Set all to nullptr
	for (int i = 0; i < new_size; i++) {
		new_map[i] = nullptr;
	}

	// Rehash all existing key-value pairs into the new map
	for (int i = 0; i < m_size; i++) {

		Node<T>* node = m_map[i];

		while(node != nullptr) {
			// Compute the new index for the current node.
			int index = hash(node->key) % new_size;

			// Insert the current node at the head of the corresponding list in the new array.
			Node<T>* next = node->next;

			node->next = new_map[index];

			new_map[index] = node;
		}
	}

	// Update the hash map
	delete[] m_map;

	m_map = new_map;
	m_size = new_size;
}
