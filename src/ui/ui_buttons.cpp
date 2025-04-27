//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <iostream>
#include <string>

//external
#include "imgui.h"

//kalavideo
#include "ui/ui_buttons.hpp"
#include "graphics/image.hpp"
#include "video/video_player.hpp"
#include "video/video_import.hpp"

using std::cout;
using std::string;

using Graphics::Image;
using Video::VideoPlayer;
using Video::VideoImport;

namespace UI
{
	static ImVec2 windowMinSize = ImVec2(0, 58.0f);
	static ImVec2 windowMaxSize = ImVec2(FLT_MAX, 58.0f);

	void UI_Buttons::DrawVideoButtons(float videoPlayerHeight)
	{
		ImGui::SetNextWindowSizeConstraints(
			windowMinSize,
			windowMaxSize);

		ImVec2 size = ImGui::GetMainViewport()->Size;
		ImGui::SetNextWindowSize(
			ImVec2(size.x, 58.0f),
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
		auto& icon_play = Image::images["icon_play"];
		if (ImGui::ImageButton(
			"play_button",                
			icon_play.textureID,
			ImVec2((float)icon_play.width, (float)icon_play.height)))
		{
			if (VideoImport::importedVideos.size() > 0)
			{
				string firstVideo = VideoImport::importedVideos.begin()->first;
				VideoPlayer::Play(firstVideo);

				cout << "Play button clicked!\n";
			}
		}

		ImGui::SameLine();
		auto& icon_pause = Image::images["icon_pause"];
		if (ImGui::ImageButton(
			"icon_pause",
			icon_pause.textureID,
			ImVec2((float)icon_pause.width, (float)icon_pause.height)))
		{
			if (VideoImport::importedVideos.size() > 0)
			{
				string firstVideo = VideoImport::importedVideos.begin()->first;
				VideoPlayer::Pause(firstVideo);

				cout << "Pause button clicked!\n";
			}
		}

		ImGui::SameLine();
		auto& icon_stop = Image::images["icon_stop"];
		if (ImGui::ImageButton(
			"icon_stop",
			icon_stop.textureID,
			ImVec2((float)icon_stop.width, (float)icon_stop.height)))
		{
			if (VideoImport::importedVideos.size() > 0)
			{
				string firstVideo = VideoImport::importedVideos.begin()->first;
				VideoPlayer::Stop(firstVideo);

				cout << "Stop button clicked!\n";
			}
		}

		ImGui::SameLine();
		auto& icon_restart = Image::images["icon_restart"];
		if (ImGui::ImageButton(
			"icon_restart",
			icon_restart.textureID,
			ImVec2((float)icon_restart.width, (float)icon_restart.height)))
		{
			if (VideoImport::importedVideos.size() > 0)
			{
				string firstVideo = VideoImport::importedVideos.begin()->first;
				VideoPlayer::Restart(firstVideo);

				cout << "Restart button clicked!\n";
			}
		}
	}
}