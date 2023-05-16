#include "console.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

void Console::clear() {
	m_messages.clear();
}

void Console::draw() {
	ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetIO().DisplaySize.y - 450));
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x - 720, 450));

	ImGui::Begin("Console", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	const float footerHeight = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing() + 3.0;
	ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footerHeight), false, ImGuiWindowFlags_HorizontalScrollbar);

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));

	for (const std::string& msg : m_messages) {;
		ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), "# ");
		ImGui::SameLine();
		ImGui::Text(msg.c_str());
	}

	if (m_scroll_to_bottom) {
		ImGui::SetScrollHereY(1.0f);
		m_scroll_to_bottom = false;
	}

	ImGui::PopStyleVar();

	ImGui::EndChild();

	ImGui::Separator();

	ImGui::Spacing();

	ImGuiInputTextFlags input_flags = ImGuiInputTextFlags_EnterReturnsTrue;

	static char inputBuf[256];

	if (ImGui::InputTextWithHint("##consoleinput", "Insert text here...", inputBuf, IM_ARRAYSIZE(inputBuf), input_flags)) {
		addMessage(inputBuf);
		inputBuf[0] = '\0';
		m_scroll_to_bottom = true;

		ImGui::SetKeyboardFocusHere(-1); // Set focus back to input field
	}

	const ImVec2 buttonSize(ImGui::CalcTextSize("Clear All").x + 50.0, 0);
	ImGui::SameLine(ImGui::GetWindowWidth() - buttonSize.x - ImGui::GetStyle().ItemSpacing.x - 10.0);

	if (ImGui::Button("Clear All", buttonSize)) {
		clear();
	}

	ImGui::End();
}

bool Console::get_new_event() const {
	return m_new_input;
}

const std::vector<std::string>& Console::get_messages() const {
	return m_messages;
}

std::vector<std::string>& Console::get_messages() {
	return m_messages;
}

void Console::set_new_event(bool event) {
	m_new_input = false;
}

void Console::addMessage(const char* msg) {
	m_messages.push_back(msg);
	m_new_input = true;
}
