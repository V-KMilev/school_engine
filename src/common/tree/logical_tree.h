#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#include "string_handle.h"

#include "stack.h"

#include "hash_map.h"
#include "pair.h"
#include "logical_tree.h"

template<typename T>
struct TreeNode {
	public:
		TreeNode(T value) :value(value), left(nullptr), right(nullptr) {}
		TreeNode(T value, TreeNode<T>* left, TreeNode<T>* right) :value(value), left(left), right(right) {}

		void fix_data(const TreeNode<T>* origin, const char& c1, const char& c2);

		TreeNode<T>* m_copy() const;

		void print() const;

	public:
		T value;

		TreeNode<T>* left;
		TreeNode<T>* right;
};

template<typename T>
void TreeNode<T>::fix_data(const TreeNode<T>* origin, const char& old_c, const char& new_c) {
	if(this == nullptr) {
		return;
	}

	if(!(origin->value == "&" || origin->value == "|" || origin->value == "!")) {
		if(origin->value[0] == old_c) {

			value[0] = new_c;
			return;
		}
	}

	left->fix_data(origin->left, old_c, new_c);
	right->fix_data(origin->right, old_c, new_c);

	return;
}

template<typename T>
TreeNode<T>* TreeNode<T>::m_copy() const {
	if(this == nullptr) {
		return nullptr;
	}

	return new TreeNode<T>(value, left->m_copy(), right->m_copy());
}

template<typename T>
void TreeNode<T>::print() const {
	if(this == nullptr) {
		return;
	}

	std::cerr << value << " ";

	right->print();
	left->print();

	return;
}

template<typename T>
class LogicalTree {
	public:
		LogicalTree();

		LogicalTree(TreeNode<T>* root);

		TreeNode<T>* get_root() const;

		void build(
			const StringArray& body,
			const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions
		);
		
		bool solve(const std::string& values) const;


		void print() const;

	private:
		TreeNode<T>* build_tree(
			const StringArray& body,
			const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions
		);

		void operator_set(
			Stack<TreeNode<T>*> &stack,
			const std::string &param,
			const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions
		);

		bool evaluate(const TreeNode<T>* node, const std::string& values) const;

	private:
		TreeNode<T>* m_root;
};

template<typename T>
LogicalTree<T>::LogicalTree() : m_root(nullptr) {}

template<typename T>
LogicalTree<T>::LogicalTree(TreeNode<T>* root) : m_root(root) {}

template<typename T>
TreeNode<T>* LogicalTree<T>::get_root() const {
	return m_root;
}

template<typename T>
void LogicalTree<T>::build(
	const StringArray& body,
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions
) {
	m_root = build_tree(body, functions);
}

template<typename T>
bool LogicalTree<T>::solve(const std::string& values) const {
	return evaluate(m_root, values);
}

template<typename T>
void LogicalTree<T>::print() const {
	m_root->print();
}

template<typename T>
TreeNode<T>* LogicalTree<T>::build_tree(
	const StringArray& body,
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions
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

template<typename T>
void LogicalTree<T>::operator_set(
	Stack<TreeNode<T>*> &stack,
	const std::string &param,
	const HashMap<Pair<std::string, LogicalTree<std::string>>>& functions
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
			TreeNode<T>* func = functions.get(param).second.get_root();

			if(func != nullptr) {
				stack.push(func);
			}
		}
		else {
			stack.push(new TreeNode<T>(param));
		}
	}
}

template<typename T>
bool LogicalTree<T>::evaluate(const TreeNode<T>* node, const std::string& values) const {
	if(node->value == "&") {
		return evaluate(node->left, values) && evaluate(node->right, values);
	}
	else if(node->value == "|") {
		return evaluate(node->left, values) || evaluate(node->right, values);
	}
	else if(node->value == "!") {
		return !evaluate(node->left, values);
	}

	for(int idx = 0; idx < values.size(); idx += 2) {
		if(node->value[0] == values[idx]) {

			if(values[idx + 1] == '1') {
				return true;
			}
			return false;
		}
	}

	std::cerr << "[evaluate ERROR] > Unexpected error\n";
	exit(-1);
}
