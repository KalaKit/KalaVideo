//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <string>
#include <iostream>

//external
extern "C"
{
#include "libavformat/avformat.h"
}
#include "platform.hpp"
#include "window.hpp"

//kalavideo
#include "core/ffmpeg.hpp"

using KalaKit::KalaWindow;
using KalaKit::PopupAction;
using KalaKit::PopupType;
using KalaKit::PopupResult;

using std::string;
using std::cout;

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
		
		cout << "[KALAKIT_FFMPEG | DEBUG] Successfully initialized ffmpeg!\n";
	}
}