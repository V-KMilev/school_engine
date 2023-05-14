#pragma once

#include "action_handle.h"

#include <vector>

class Controller {
	public:
		Controller();
	
		void reset();

		void update(const std::vector<std::string>& messages);

		void draw() const;

	private:
		void defines() const;

		void solves() const;

		void alls() const;


	private:
		ActionHandle m_ah;
};
