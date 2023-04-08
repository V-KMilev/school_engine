#pragma once

#include <iostream>
#include <string>

#include "string_handle.h"

template<typename T>
struct TreeNode {
	public:
		TreeNode(T value) :value(value), left(nullptr), right(nullptr) {}
		TreeNode(T value, TreeNode<T>* left, TreeNode<T>* right) :value(value), left(left), right(right) {}

		~TreeNode() {
			delete_sub_tree(left);
			delete_sub_tree(right);
		}

	private:
		void delete_sub_tree(TreeNode<T>*& node) {
			if (node) {
				delete_sub_tree(node->left);
				delete_sub_tree(node->right);

				delete node;
				node = nullptr;
			}
		}

	public:
		T value;

		TreeNode<T>* left;
		TreeNode<T>* right;
};

class LogicalTree {
	public:
		LogicalTree(const std::string &body) : m_root(nullptr) {
			StringHandle sh;
			m_body = sh.remove_symbol(body, ' ');
		}

		LogicalTree() : m_root(nullptr), m_body("") {}

		~LogicalTree() {}

		void create() {
			m_root = create_from_root(0, m_body.size() - 1);
		}

		void print() {
			print_tree(m_root);
		}

		TreeNode<char>* get_root() const {
			return m_root;
		}

		void set_body(const std::string &body) {
			StringHandle sh;
			m_body = sh.remove_symbol(body, ' ');
		}

	private:
		TreeNode<char>* create_from_root(int start, int end) {
			// If start and end are the same, we have a leaf node
			if(start == end) {
				return new TreeNode<char>(m_body[start]);
			}

			// Find the index to split the expression into two subtrees
			int split_index = find_split_index(start, end);

			// Recursively create the left and right subtrees
			TreeNode<char>* left_sub_tree  = create_from_root(start, split_index - 1);
			TreeNode<char>* right_sub_tree = create_from_root(split_index + 1, end);

			// Create a new node with the split operator and left/right subtrees as children
			return new TreeNode<char>(m_body[split_index], left_sub_tree, right_sub_tree);
		}

		// TODO: Add prio to operations
		int find_split_index(int start, int end) {
			int bracket_count = 0;

			// From the end to the start
			for (int idx = end; idx >= start; idx--) {
				const char& current_char = m_body[idx];

				// Increment bracket count for each opening bracket
				if (current_char == '(') {
					bracket_count++;

				// Decrement bracket count for each closing bracket
				} else if (current_char == ')') {
					bracket_count--;

				// If we encounter an operator and the bracket count is 0 or less, update the split index
				} else if (bracket_count <= 0 && (
					current_char == '&' ||
					current_char == '|' ||
					current_char == '!'
				)) {
					return idx;
				}
			}

			// If no split index was found, return the end index
			return end;
		}

		void print_tree(TreeNode<char>* node) {
			if (node) {
				print_tree(node->left);
				std::cout << node->value << " ";
				print_tree(node->right);
			}
		}

	private:
		TreeNode<char>* m_root;

		std::string m_body;
};
