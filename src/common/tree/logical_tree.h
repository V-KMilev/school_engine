#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#include "string_handle.h"

template<typename T>
struct TreeNode {
	public:
		TreeNode(T value) :value(value), left(nullptr), right(nullptr) {}
		TreeNode(T value, TreeNode<T>* left, TreeNode<T>* right) :value(value), left(left), right(right) {}

		~TreeNode() {
			delete left;
			delete right;
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

		~LogicalTree() {
			delete m_root;
		}

		void set_body(const std::string &body) {
			StringHandle sh;
			m_body = sh.remove_symbol(body, ' ');
		}

		void build() {
			int index = 0;
			m_root = build_tree(m_body, index);
		}

		void printTree(TreeNode<char>* node) {
			if (node == nullptr) {
				return;
			}

			printTree(node->left);

			std::cout << " " << node->value;

			printTree(node->right);
		}

		void print() {
			printTree(m_root);
		}

	private:
		TreeNode<char>* build_tree(const std::string& equation, int index) {
			const char& c = equation[index];

			TreeNode<char>* root = new TreeNode<char>(c);

			if(root->value == '!') {
				index++;

				TreeNode<char>* symbol = new TreeNode<char>(equation[index]);
				root->left = symbol;
			}

			index++;

			if(index < equation.size()) {
				const char& op = equation[index];

				if(op == '&' || op == '|') {
					TreeNode<char>* node = new TreeNode<char>(op);

					node->left = root;
					node->right = build_tree(equation, index + 1);

					return node;
				}
			}

			return root;
		}

	private:
		TreeNode<char>* m_root;

		std::string m_body;
};
