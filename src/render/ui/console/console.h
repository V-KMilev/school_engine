#pragma once

#include <string>
#include <vector>

class Console {
	public:
		Console() {
			clear();
		}

		void clear();

		void draw();

		bool get_new_event() const;

		const std::vector<std::string>& get_messages() const;

		std::vector<std::string>& get_messages();

		void set_new_event(bool event);

	private:
		void addMessage(const char* msg);

	private:
		std::vector<std::string> m_messages;

		bool m_new_input = false;

		bool m_scroll_to_bottom = true;
};
