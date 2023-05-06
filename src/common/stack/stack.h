#pragma once

template <typename T>
struct StackNode {
	public:
		StackNode(T value) :value(value), left(nullptr) {}
		StackNode(T value, StackNode<T>* next) : value(value), next(next) {}

	public:
		T value;
		StackNode<T>* next;
};

template <typename T>
class Stack {
	public:
		Stack() : m_top(nullptr) {}

		~Stack() {
			while (m_top != nullptr) {

				StackNode<T>* temp = m_top;
				m_top = m_top->next;

				delete temp;
			}
		}

		void push(T value) {
			StackNode<T>* newTop = new StackNode<T>(value, m_top);

			m_top = newTop;
		}

		T pop() {
			if (m_top == nullptr) {
				return T();
			}

			StackNode<T>* temp = m_top;

			m_top = m_top->next;

			T value = temp->value;

			delete temp;
			return value;
		}

		T top() const {
			if (m_top == nullptr) {
				return T();
			}

			return m_top->value;
		}

		bool empty() const {
			return m_top == nullptr;
		}

	private:
		StackNode<T>* m_top;
};
