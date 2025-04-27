//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <iostream>
#include <string>

//external
#include "window.hpp"
#include "opengl.hpp"

//kalavideo
#include "core/core.hpp"
#include "core/ffmpeg.hpp"
#include "ui/ui_core.hpp"
#include "video/video_import.hpp"
#include "graphics/graphics_core.hpp"
#include "graphics/image.hpp"

using std::string;
using std::cout;

using KalaKit::KalaWindow;
using KalaKit::OpenGL;
using UI::UI_Core;
using Graphics::Graphics_Core;
using Graphics::Image;
using Video::VideoImport;

namespace Core
{
	void KalaVideo::Initialize()
	{
		//KalaWindow::SetDebugType(DebugType::DEBUG_FREETYPE_FONT_TEST);
		Graphics_Core::Initialize();

		Ffmpeg::Initialize();
	}
		
	void KalaVideo::Update()
	{
		cout << "Successfully reached render loop!\n";

		while (!KalaWindow::ShouldClose())
		{
			KalaWindow::Update();

			if (OpenGL::isInitialized) Graphics_Core::Update();
		}
	}

	void KalaVideo::Shutdown()
	{
		VideoImport::Shutdown();
		Image::Shutdown();
		UI_Core::Shutdown();

		cout << "Successfully shut down KalaVideo!\n";
	}
}