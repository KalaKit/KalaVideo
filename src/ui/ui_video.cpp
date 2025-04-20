//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <iostream>

//external
#include "imgui.h"

//kalavideo
#include "ui/ui_video.hpp"
#include "ui/ui_core.hpp"

using std::cout;

namespace UI
{
	static ImVec2 windowMinSize = ImVec2(300, 300);
	static ImVec2 windowMaxSize = ImVec2(FLT_MAX, FLT_MAX);

	void UI_Video::DrawVideoWindow()
	{
		ImGui::SetNextWindowSizeConstraints(
			windowMinSize,
			windowMaxSize);

		ImVec2 size = ImGui::GetMainViewport()->Size;
		float targetHeight = size.y * 0.85f;
		ImGui::SetNextWindowSize(
			ImVec2(size.x, targetHeight),
			ImGuiCond_Always);
		ImGui::SetNextWindowPos(
			ImVec2(0, 0),
			ImGuiCond_Always);

		ImGuiWindowFlags winFlags =
			ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoSavedSettings;

		if (ImGui::Begin("Video", nullptr, winFlags))
		{
			ImGui::Text("this is the main KalaVideo window.");
			ImGui::End();
		}
	}
}