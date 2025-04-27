//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

//external
#include "imgui.h"

//kalavideo
#include "ui/ui_buttons.hpp"

namespace UI
{
	static ImVec2 windowMinSize = ImVec2(0, 80.0f);
	static ImVec2 windowMaxSize = ImVec2(FLT_MAX, 80.0f);

	void UI_Buttons::DrawVideoButtons(float videoPlayerHeight)
	{
		ImGui::SetNextWindowSizeConstraints(
			windowMinSize,
			windowMaxSize);

		ImVec2 size = ImGui::GetMainViewport()->Size;
		ImGui::SetNextWindowSize(
			ImVec2(size.x, 80.0f),
			ImGuiCond_Always);
		ImGui::SetNextWindowPos(
			ImVec2(0, videoPlayerHeight),
			ImGuiCond_Always);

		ImGuiWindowFlags winFlags =
			ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoSavedSettings
			| ImGuiWindowFlags_NoTitleBar;

		if (ImGui::Begin("VideoButtons", nullptr, winFlags))
		{
			DrawVideoButtonsContent();
			ImGui::End();
		}
	}

	void UI_Buttons::DrawVideoButtonsContent()
	{
		ImGui::Text("video player buttons...");
	}
}