//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

//external
#include "imgui.h"

//kalavideo
#include "ui/ui_editor.hpp"

namespace UI
{
	static ImVec2 windowMinSize = ImVec2(0, 100);
	static ImVec2 windowMaxSize = ImVec2(FLT_MAX, FLT_MAX);

	void UI_Editor::DrawVideoEditor(float totalFinalHeight)
	{
		ImGui::SetNextWindowSizeConstraints(
			windowMinSize,
			windowMaxSize);

		ImVec2 size = ImGui::GetMainViewport()->Size;
		float remainingHeight = size.y - totalFinalHeight;
		ImGui::SetNextWindowSize(
			ImVec2(size.x, remainingHeight),
			ImGuiCond_Always);
		ImGui::SetNextWindowPos(
			ImVec2(0, totalFinalHeight),
			ImGuiCond_Always);

		ImGuiWindowFlags winFlags =
			ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoSavedSettings
			| ImGuiWindowFlags_NoTitleBar;

		if (ImGui::Begin("VideoEditor", nullptr, winFlags))
		{
			DrawVideoEditorContent();
			ImGui::End();
		}
	}

	void UI_Editor::DrawVideoEditorContent()
	{
		ImGui::Text("video editor...");
	}
}