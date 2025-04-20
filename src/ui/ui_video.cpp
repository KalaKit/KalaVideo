//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <iostream>

//external
#include "imgui.h"

//kalavideo
#include "ui_video.hpp"
#include "ui_core.hpp"

using std::cout;

namespace UI
{
	static ImVec2 windowMinSize = ImVec2(300, 300);
	static ImVec2 windowMaxSize = ImVec2(FLT_MAX, FLT_MAX);
	static ImVec2 windowSize = ImVec2(400, 400);

	void UI_Video::DrawVideoWindow()
	{
		ImGui::SetNextWindowSizeConstraints(
			windowMinSize,
			windowMaxSize);
		ImGui::SetNextWindowSize(
			windowSize,
			ImGuiCond_FirstUseEver);
		kvec2 windowSizeKvec2 = kvec2(windowSize.x, windowSize.y);
		kvec2 centerPosKvec2 = UI_Core::CenterWindow(windowSizeKvec2);
		ImVec2 centerPos = ImVec2(centerPosKvec2.x, centerPosKvec2.y);
		ImGui::SetNextWindowPos(
			centerPos,
			ImGuiCond_FirstUseEver);

		ImGuiWindowFlags winFlags =
			ImGuiWindowFlags_NoCollapse;

		if (ImGui::Begin("Video"), NULL, winFlags)
		{
			ImGui::Text("this is the main KalaVideo window.");

			ImGui::End();
		}
	}
}