#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "console.h"
#include "controller.h"

#include "config.h"

class UIHandle {
	public:
		void setup(GLFWwindow* window, const char* gl_version);

		void newframe() const;

		void shutdown() const;

		void render() const;

		void content();

	private:

	private:
		void setStyle() const;

	private:
		Console m_console;
		Controller m_controller;

		// Style members
		ImVec4 mDefault = ImVec4(0.0f, 0.478f, 0.800f, 1.0f);
		ImVec4 mHovered = ImVec4(0.0f, 0.392f, 0.722f, 1.0f);
		ImVec4 mActive  = ImVec4(0.0f, 0.361f, 0.918f, 1.0f);

		ImVec4 mBackground     = ImVec4(0.118f, 0.118f, 0.125f, 1.0f);
		ImVec4 mMenuBackground = ImVec4(0.098f, 0.098f, 0.106f, 1.0f);
};


void UIHandle::setup(GLFWwindow* window, const char* gl_version) {
	/* ImGui Setup */
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(gl_version);

	setStyle();
}

void UIHandle::newframe() const {
	/* ImGui New Frame */
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void UIHandle::shutdown() const {
	/* ImGui Shutdown */
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UIHandle::render() const {
	/* ImGui Render */
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIHandle::content() {

	static bool run_new  = false;
	static bool run_open = false;
	static bool run_save = false;

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			ImGui::MenuItem("Open", "Ctrl + O", &run_open);
			ImGui::MenuItem("Save", "Ctrl + S", &run_save);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	if(run_open) {
		m_controller.open(run_open);
	}

	if(run_save) {
		m_controller.save(run_save);
	}

	m_console.draw();

	if(m_console.get_new_event()) {
		m_controller.update(m_console.get_messages());

		m_console.set_new_event(false);
	}

	m_controller.draw();

	ImGuiWindowFlags mWindowFlags = 
		ImGuiWindowFlags_NoTitleBar         | ImGuiWindowFlags_AlwaysAutoResize |
		ImGuiWindowFlags_NoCollapse         | ImGuiWindowFlags_NoSavedSettings  |
		ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_MenuBar;

	//ImGui::ShowDemoWindow();
}

void UIHandle::setStyle() const {
	/* ImGui Style */
	ImGuiStyle& style = ImGui::GetStyle();

	style.FrameBorderSize = 1.0f;
	style.WindowBorderSize = 0.0f;

	ImGui::SetColorEditOptions(ImGuiColorEditFlags_PickerHueWheel);

	ImVec4* colors = ImGui::GetStyle().Colors;

	ImGui::GetStyle().PopupBorderSize = 0.0f;
	ImGui::GetStyle().GrabMinSize     = 13.0f;
	ImGui::GetStyle().ScrollbarSize   = 15.0f;

	ImGui::GetStyle().IndentSpacing    = 30.0f;
	ImGui::GetStyle().ItemSpacing      = ImVec2(7.0f, 3.0f);
	ImGui::GetStyle().FramePadding     = ImVec2(4.0f, 3.0f);
	ImGui::GetStyle().WindowPadding    = ImVec2(2.0f, 6.0f);
	ImGui::GetStyle().ItemInnerSpacing = ImVec2(3.0f, 3.0f);

	ImGui::GetStyle().WindowRounding    = 0.0f;
	ImGui::GetStyle().GrabRounding      = 7.0f;
	ImGui::GetStyle().PopupRounding     = 7.0f;
	ImGui::GetStyle().FrameRounding     = 7.0f;
	ImGui::GetStyle().ScrollbarRounding = 7.0f;

	ImGui::GetStyle().WindowTitleAlign = ImVec2(0.5f, 0.5f);

	colors[ImGuiCol_WindowBg]             = mBackground;

	colors[ImGuiCol_MenuBarBg]            = mMenuBackground;

	colors[ImGuiCol_TitleBgActive]        = mDefault;
	colors[ImGuiCol_TitleBg]              = mHovered;

	colors[ImGuiCol_Button]               = mDefault;
	colors[ImGuiCol_ButtonHovered]        = mHovered;
	colors[ImGuiCol_ButtonActive]         = mActive;

	colors[ImGuiCol_SliderGrab]           = mDefault;
	colors[ImGuiCol_SliderGrabActive]     = mActive;

	colors[ImGuiCol_FrameBg]              = ImVec4(mDefault.x / 1.5f, mDefault.y / 2.0f, mDefault.z / 1.5f, 1.0f);
	colors[ImGuiCol_FrameBgHovered]       = ImVec4(mHovered.x / 1.5f, mHovered.y / 2.0f, mHovered.z / 1.5f, 1.0f);
	colors[ImGuiCol_FrameBgActive]        = ImVec4(mActive.x  / 1.5f, mActive.y  / 2.0f, mActive.z  / 1.5f, 1.0f);

	colors[ImGuiCol_CheckMark]            = mActive;
	colors[ImGuiCol_Separator]            = mActive;

	colors[ImGuiCol_ScrollbarBg]          = ImVec4(mHovered.x / 1.5f, mHovered.y / 1.5f, mHovered.z / 1.5f, 1.0f);
	colors[ImGuiCol_ScrollbarGrab]        = mDefault;
	colors[ImGuiCol_ScrollbarGrabHovered] = mHovered;
	colors[ImGuiCol_ScrollbarGrabActive]  = mActive;

	colors[ImGuiCol_ResizeGrip]           = mHovered;
	colors[ImGuiCol_ResizeGripHovered]    = mDefault;
	colors[ImGuiCol_ResizeGripActive]     = mDefault;

	colors[ImGuiCol_Header]               = mDefault;
	colors[ImGuiCol_HeaderHovered]        = mHovered;
	colors[ImGuiCol_HeaderActive]         = mActive;

	colors[ImGuiCol_Tab]                  = mDefault;
	colors[ImGuiCol_TabHovered]           = mHovered;
	colors[ImGuiCol_TabActive]            = mActive;

	colors[ImGuiCol_TextSelectedBg]       = mHovered;
}
