#include "file_handle.h"

FileHandle::FileHandle() : m_path("./logs/last_save.txt"), m_auto_save(AutoSaveMode::ON) {}

FileHandle::FileHandle(const std::string& path) : m_path(path), m_auto_save(AutoSaveMode::ON) {}

void FileHandle::set_auto_save(AutoSaveMode mode) {
	m_auto_save = mode;
}

void FileHandle::save(const ActionHandle& ah) {

}

ActionHandle FileHandle::read() const {
	ActionHandle ah;
	return ah;
}

void FileHandle::leave_check(const ActionHandle& ah) {
	if(m_auto_save != AutoSaveMode::ON) {
		return;
	}

	save(ah);
}
