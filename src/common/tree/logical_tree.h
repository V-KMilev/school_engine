#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#include "string_handle.h"

#include "stack.h"

#include "hash_map.h"
#include "pair.h"
#include "logical_tree.h"

#include "function_handle.h"

template<typename T>
struct TreeNode {
	public:
		TreeNode(T value) :value(value), left(nullptr), right(nullptr) {}
		TreeNode(T value, TreeNode<T>* left, TreeNode<T>* right) :value(value), left(left), right(right) {}

	public:
		T value;

		TreeNode<T>* left;
		TreeNode<T>* right;
};

template<typename T>
class LogicalTree {
	public:
		LogicalTree() : m_root(nullptr) {}

		TreeNode<T>* get_root() const {
			return m_root;
		}

		void build(
			const StringArray& body,
			const HashMap<LogicalTree<T>>& functions
		) {
			m_root = build_tree(body, functions);
		}

		void printTree(TreeNode<T>* node) const {
			if (node == nullptr) {
				return;
			}

			std::cout << " " << node->value;

			printTree(node->right);
			printTree(node->left);
		}

		void print() const {
			printTree(m_root);
		}

	private:
		// TODO: Finish function sets
		TreeNode<T>* build_tree(
			const StringArray& body,
			const HashMap<LogicalTree<T>>& functions
		) {
			Stack<TreeNode<T>*> stack;
			Stack<TreeNode<T>*> braket_stack;

			for (int idx = body.count(); idx >= 0; idx--) {

				const std::string& data = body.data()[idx];

				if(data == ")") {

					while(body.data()[--idx] != "(") {
						operator_set(braket_stack, body.data()[idx], functions);
					}

					TreeNode<T>* right = braket_stack.pop();
					TreeNode<T>* braket_root = braket_stack.pop();
					braket_root->right = right;

					stack.push(braket_root);
				}
				else {
					operator_set(stack, data, functions);
				}
			}

			TreeNode<T>* right = stack.pop();
			TreeNode<T>* root = stack.pop();
			root->right = right;

			return root;
		}

		void operator_set(
			Stack<TreeNode<T>*> &stack,
			const std::string &param,
			const HashMap<LogicalTree<T>>& functions
		) {
			if(param == "&" || param == "|") {
				TreeNode<T>* node = new TreeNode<T>(param);

				node->left  = stack.pop();
				node->right = stack.pop();

				stack.push(node);
			}
			else if (param == "!") {
				TreeNode<T>* node = new TreeNode<T>(param);

				node->left = stack.pop();

				stack.push(node);
			}
			else {
				if(param.size() > 1) {
					TreeNode<T>* func = functions.get(param).get_root();

					if(func != nullptr) {
						stack.push(func);
					}
				}
				else {
					stack.push(new TreeNode<T>(param));
				}
			}
		}

	private:
		TreeNode<T>* m_root;
};
