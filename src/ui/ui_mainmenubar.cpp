//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <iostream>

//external
#include "imgui.h"
#include "window.hpp"

//kalavideo
#include "ui/ui_mainmenubar.hpp"

using KalaKit::KalaWindow;

using std::cout;

namespace UI
{
	void UI_MainMenuBar::Update()
	{
		ImGui::BeginMainMenuBar();

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save project"))
			{
				cout << "!!!! save\n";
			}

			if (ImGui::MenuItem("Load project"))
			{
				cout << "!!!! load\n";
			}

			if (ImGui::MenuItem("Exit")) KalaWindow::SetShouldCloseState(true);

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Import"))
		{
			if (ImGui::MenuItem("Import video"))
			{
				cout << "!!!! import video file\n";
			}

			if (ImGui::MenuItem("Import audio"))
			{
				cout << "!!!! import audio file\n";
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Video player"))
			{
				cout << "!!!! show video player\n";
			}

			if (ImGui::MenuItem("Video editor"))
			{
				cout << "!!!! show video editor\n";
			}

			if (ImGui::MenuItem("Video list"))
			{
				cout << "!!!! show video list\n";
			}

			if (ImGui::MenuItem("Edit tools"))
			{
				cout << "!!!! show edit tools\n";
			}

			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Export"))
		{
			cout << "!!!! export\n";
		}

		ImGui::EndMainMenuBar();
	}
}