//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <string>
#include <iostream>
#include <filesystem>

//external
extern "C"
{
#include "libavformat/avformat.h"
}
#include "window.hpp"

//kalavideo
#include "core/ffmpeg.hpp"
#include "video/video_import.hpp"

using std::string;
using std::filesystem::current_path;
using std::filesystem::create_directory;
using std::filesystem::path;
using std::filesystem::exists;
using std::filesystem::directory_iterator;
using std::cout;

using KalaKit::KalaWindow;
using KalaKit::PopupAction;
using KalaKit::PopupType;
using KalaKit::PopupResult;
using Video::VideoImport;

namespace Core
{
	void Ffmpeg::Initialize()
	{
		av_log_set_level(AV_LOG_ERROR);

		AVFormatContext* ctx = avformat_alloc_context();
		if (!ctx)
		{
			string title = "ffmpeg initialize error";
			string message = "Failed to initialize ffmpeg!";
			cout << message << "\n";
			if ((KalaWindow::CreatePopup(
				title,
				message,
				PopupAction::POPUP_ACTION_OK,
				PopupType::POPUP_TYPE_ERROR)) 
				== PopupResult::POPUP_RESULT_OK)
			{
				KalaWindow::SetShouldCloseState(true);
				return;
			}
		}
		
		avformat_free_context(ctx);

		path videosFolder = path(current_path() / "videos");
		if (!exists(videosFolder))
		{
			create_directory(videosFolder);
			cout << "Created new videos folder: " << videosFolder << "\n";
		}

		for (const auto& file : directory_iterator(videosFolder))
		{
			string extension = path(file).extension().string();
			if (extension == ".mp4"
				|| extension == ".mov"
				|| extension == ".mkv"
				|| extension == ".webm")
			{
				string filePath = path(file).string();
				VideoImport::ImportVideo(filePath);
			}
			else
			{
				string fileName = path(file).filename().string();
				cout << "Error: Found invalid file " << fileName << " in videos folder! This should not be placed there.\n";
			}
		}
		
		cout << "Successfully initialized ffmpeg!\n";
	}
}