#pragma once

#include <vector>

#include "action_handle.h"
#include "file_handle.h"

class Controller {
	public:
		Controller();
	
		void reset();

		void update(const std::vector<std::string>& messages);

		void draw() const;

		void save(bool& flag) const;

		void open(bool& flag);

	private:
		void defines() const;

		void solves() const;

		void alls() const;


	private:
		ActionHandle m_ah;
		FileHandle m_fh;
};
