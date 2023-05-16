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
		TreeNode(T value);
		TreeNode(T value, TreeNode<T>* left, TreeNode<T>* right);

		TreeNode(TreeNode<T>* copy);

		TreeNode<T>& operator == (const TreeNode& copy);

		bool operator == (const TreeNode& other) const;

		void fix_data(const TreeNode<T>* origin, const char& c1, const char& c2);

		TreeNode<T>* m_copy() const;

		void print() const;

	public:
		T value;

		TreeNode<T>* left;
		TreeNode<T>* right;
};

template<typename T>
TreeNode<T>::TreeNode(T value) :value(value), left(nullptr), right(nullptr) {}

template<typename T>
TreeNode<T>::TreeNode(T value, TreeNode<T>* left, TreeNode<T>* right) :value(value), left(left), right(right) {}

template<typename T>
TreeNode<T>::TreeNode(TreeNode<T>* copy) {
	value = copy->value;

	left = new TreeNode<T>(copy->left->value);
	right = new TreeNode<T>(copy->right->value);
}

template<typename T>
TreeNode<T>& TreeNode<T>::operator == (const TreeNode& copy) {
	value = copy->value;

	left = new TreeNode<T>(copy->left->value);
	right = new TreeNode<T>(copy->right->value);
}

template<typename T>
bool TreeNode<T>::operator == (const TreeNode& other) const {
	return value == other.value && left == other.left && right == other.right;
}

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

		LogicalTree(const LogicalTree& copy);

		LogicalTree(TreeNode<T>* root);

		LogicalTree<T>& operator = (const LogicalTree& copy);

		LogicalTree<T>& operator = (TreeNode<T>* root);

		bool operator == (const LogicalTree& other) const;

		operator std::string () const {
			return get_in_string(m_root);
		}

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

		std::string get_in_string(const TreeNode<T>* node) const;

	private:
		TreeNode<T>* m_root;
};

template<typename T>
LogicalTree<T>::LogicalTree() : m_root(nullptr) {}

template<typename T>
LogicalTree<T>::LogicalTree(const LogicalTree& copy) {
	m_root = copy.m_root;
}

template<typename T>
LogicalTree<T>::LogicalTree(TreeNode<T>* root) {
	m_root = new TreeNode<T>(root);
}

template<typename T>
LogicalTree<T>& LogicalTree<T>::operator = (const LogicalTree& copy) {
	m_root = copy.m_root;

	return *this;
}

template<typename T>
LogicalTree<T>& LogicalTree<T>::operator = (TreeNode<T>* root) {
	m_root = new TreeNode<T>(root);

	return *this;
}

template<typename T>
bool LogicalTree<T>::operator == (const LogicalTree& other) const {
	return m_root == other.m_root;
}


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

	for (int idx = 0; idx < body.count(); idx++) {

		const std::string param = body.data()[idx];

		operator_set(stack, param, functions);
	}

	return stack.pop();
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

	else if(
		!stack.empty() &&
		stack.top()->value == "!" &&
		stack.top()->left == nullptr
	) {
		if(param.size() > 1) {
			TreeNode<T>* func = functions.get(param).second.get_root();

			if(func != nullptr) {
				stack.push(func);
			}
		}
		else {
			stack.push(new TreeNode<T>(param));
		}

		stack.top()->left = stack.pop();
		return;
	}

	else if (param == "!") {
		stack.push(new TreeNode<T>(param));
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
template<typename T>
std::string LogicalTree<T>::get_in_string(const TreeNode<T>* node) const {
	if (node == nullptr) {
		return "";
	}

	std::string left = "";
	std::string right = "";

	if(node->left != nullptr) {
		left = get_in_string(node->left);
	}

	if(node->right != nullptr) {
		right = get_in_string(node->right);
	}

	if(node->value == "!") {
		return " " + node->value + left;
	}

	return right + left + " " + node->value;
}
