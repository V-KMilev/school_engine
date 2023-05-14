#pragma once

#include <string>

#include "action_handle.h"

enum class AutoSaveMode : bool {
	OFF = false,
	ON = true
};

class FileHandle {
	public:
		FileHandle();

		FileHandle(const std::string& path);

		void set_auto_save(AutoSaveMode mode);

		void save(const ActionHandle& ah, const std::string& path = "") const;

		ActionHandle read() const;

		void leave_check(const ActionHandle& ah) const;

		std::string path() const;

	private:
		// Default set to "last_save.txt"
		std::string m_path;
		// Default set to on (true)
		AutoSaveMode m_auto_save;
};
