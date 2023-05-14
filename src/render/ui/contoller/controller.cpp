#include "controller.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <string>

Controller::Controller() {}

void Controller::reset() {}

void Controller::update(const std::vector<std::string>& messages) {
	m_ah.handle_input(messages[messages.size() - 1]);
}

void Controller::draw() const {
	float menu_bar_height = ImGui::GetFrameHeight();

	ImGui::SetNextWindowPos(ImVec2(1200, menu_bar_height));
	ImGui::SetNextWindowSize(ImVec2(720, ImGui::GetIO().DisplaySize.y));

	ImGui::Begin("ConsoleA", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

	defines();

	solves();

	alls();

	static bool showCheckbox = true;
	ImGui::Checkbox("Show text block", &showCheckbox);

	if (showCheckbox) {
		ImGui::Text("This is a text block that will appear or disappear based on the checkbox above.");
	}

	ImGui::End();
}

void Controller::defines() const {
	ImGui::Separator();

	ImGui::TextColored(ImVec4(0.5, 0.5, 1.0, 1.0), "DEFINES");

	ImGui::Spacing();

	ImGui::BeginChild("Defines", ImVec2(200, 200), true);

	static std::string func_value = "";

	for(int idx = 0; idx < m_ah.get_functions().get_size(); idx++) {
		HashNode<Pair<std::string, LogicalTree<std::string>>>* node = m_ah.get_functions().get_map()[idx];

		while(node != nullptr) {
			std::string func_name = node->key;
			
			if(ImGui::Selectable(func_name.c_str())) {
				func_value = node->value.second;
				func_value += "\n";
				func_value += node->value.first;
			}
	
			node = node->next;
		}
	}

	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("dBody", ImVec2(0, 200), true);

	ImGui::TextWrapped("%s", func_value.c_str());

	ImGui::EndChild();

	ImGui::Spacing();

	ImGui::Separator();

}

void Controller::solves() const {
	ImGui::Separator();

	ImGui::TextColored(ImVec4(0.5, 0.5, 1.0, 1.0), "SOLVES");

	ImGui::Spacing();

	ImGui::BeginChild("Solves", ImVec2(200, 200), true);

	static std::string func_value = "";

	for(int idx = 0; idx < m_ah.get_solves().get_size(); idx++) {
		HashNode<Pair<std::string, bool>>* node = m_ah.get_solves().get_map()[idx];

		while(node != nullptr) {
			std::string func_name = node->key;
			
			if(ImGui::Selectable(func_name.c_str())) {
				if(node->value.second == 1) {
					func_value = "1";
				}
				else {
					func_value = "0";
				}

				func_value += "\n";
				func_value += node->value.first;
			}
	
			node = node->next;
		}
	}

	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("sBody", ImVec2(0, 200), true);

	ImGui::TextWrapped("%s", func_value.c_str());

	ImGui::EndChild();

	ImGui::Spacing();

	ImGui::Separator();
}

void Controller::alls() const {
	ImGui::Separator();

	ImGui::TextColored(ImVec4(0.5, 0.5, 1.0, 1.0), "ALLS");

	ImGui::Spacing();

	ImGui::BeginChild("Alls", ImVec2(200, 200), true);

	static std::string func_value = "";

	for(int idx = 0; idx < m_ah.get_all_solves().get_size(); idx++) {
		HashNode<int>* solve = m_ah.get_all_solves().get_map()[idx];

		while(solve != nullptr) {
			std::string func_name = solve->key;

			if(ImGui::Selectable(func_name.c_str())) {
				func_value += std::to_string(solve->value);
			}

			solve = solve->next;
		}
	}

	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("aBody", ImVec2(0, 200), true);

	ImGui::TextWrapped("%s", func_value.c_str());

	ImGui::EndChild();

	ImGui::Spacing();

	ImGui::Separator();
}