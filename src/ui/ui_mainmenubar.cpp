//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <iostream>
#include <string>
#include <filesystem>

//external
#include "imgui.h"
#include "window.hpp"

//kalavideo
#include "ui/ui_mainmenubar.hpp"
#include "video/video_import.hpp"

using std::error_code;
using std::string;
using std::filesystem::exists;
using std::filesystem::copy_file;
using std::filesystem::remove;
using std::filesystem::current_path;
using std::filesystem::path;
using std::cout;

using KalaKit::KalaWindow;
using KalaKit::FileType;
using Video::VideoImport;
using KalaKit::PopupAction;
using KalaKit::PopupType;
using KalaKit::PopupResult;

namespace UI
{
	void UI_MainMenuBar::Update()
	{
		ImGui::BeginMainMenuBar();

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New project"))
			{
				cout << "!!!!create new project\n";
			}

			if (ImGui::MenuItem("Save project"))
			{
				cout << "!!!! save current project\n";
			}

			if (ImGui::MenuItem("Load project"))
			{
				cout << "!!!! load existing project\n";
			}

			if (ImGui::MenuItem("Exit")) KalaWindow::SetShouldCloseState(true);

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Import"))
		{
			if (ImGui::MenuItem("Import video"))
			{
				ImportVideo();
			}

			if (ImGui::MenuItem("Import audio"))
			{
				string chosenFile = KalaWindow::FileExplorer(FileType::FILE_ANY_AUDIO);

				cout << "chose audio file: " << chosenFile << "\n";
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

	void UI_MainMenuBar::ImportVideo()
	{
		path videosPath = path(current_path() / "videos");

		string chosenFile = KalaWindow::FileExplorer(FileType::FILE_ANY_VIDEO);

		path origin = path(chosenFile);
		string fileName = origin.filename().string();
		path target = path(videosPath / fileName);

		if (exists(target))
		{
			string existsMessage = "Error: Cannot import video file '" + fileName + "' because it already exists!";
			
			cout << existsMessage << "\n";

			if ((KalaWindow::CreatePopup(
				"Video import failed",
				existsMessage,
				PopupAction::POPUP_ACTION_OK,
				PopupType::POPUP_TYPE_ERROR))
				== PopupResult::POPUP_RESULT_OK)
			{

			}
		}
		else
		{
			error_code copyEC;
			bool copySuccess = copy_file(origin, target, copyEC);

			if (!copySuccess)
			{
				string copyFailMessage = "Error: Failed to copy video. Reason: " + copyEC.message();
				
				cout << copyFailMessage << "\n";

				if ((KalaWindow::CreatePopup(
					"Video import failed",
					copyFailMessage,
					PopupAction::POPUP_ACTION_OK,
					PopupType::POPUP_TYPE_ERROR))
					== PopupResult::POPUP_RESULT_OK)
				{

				}
			}
			else
			{
				cout << "Copied video from '" << origin << "' to '" << target << "'!\n";

				string stringTarget = target.string();
				bool success = VideoImport::ImportVideo(stringTarget);
				if (!success)
				{
					string title = "Video import failed";
					string importFailMessage = VideoImport::failReason;

					cout << importFailMessage << "\n";

					if ((KalaWindow::CreatePopup(
						"Video import failed",
						importFailMessage,
						PopupAction::POPUP_ACTION_OK,
						PopupType::POPUP_TYPE_ERROR))
						== PopupResult::POPUP_RESULT_OK)
					{
						VideoImport::failReason = "";
						error_code removeEC;
						bool removeSuccess = remove(target, removeEC);
						if (!removeSuccess)
						{
							string removeMessage = "Error: Failed to delete video. Reason: " + removeEC.message();
							
							cout << removeMessage << "\n";

							if ((KalaWindow::CreatePopup(
								"Video import failed",
								removeMessage,
								PopupAction::POPUP_ACTION_OK,
								PopupType::POPUP_TYPE_ERROR))
								== PopupResult::POPUP_RESULT_OK)
							{

							}
						}
					}
				}
			}
		}
	}
}