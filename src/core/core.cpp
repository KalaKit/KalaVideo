//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <iostream>

//external
#include "window.hpp"
#include "opengl.hpp"

//kalavideo
#include "core/core.hpp"
#include "ui/ui_core.hpp"
#include "graphics/graphics_core.hpp"

using std::cout;

using KalaKit::KalaWindow;
using KalaKit::OpenGL;
using UI::UI_Core;
using Graphics::Graphics_Core;

namespace Core
{
	void KalaVideo::Initialize()
	{
		//KalaWindow::SetDebugType(DebugType::DEBUG_FREETYPE_FONT_TEST);
		Graphics_Core::Initialize();
	}
		
	void KalaVideo::Update()
	{
		cout << "[KALAKIT_VIDEO | DEBUG] Successfully reached render loop!\n";

		while (!KalaWindow::ShouldClose())
		{
			KalaWindow::Update();

			if (OpenGL::isInitialized) Graphics_Core::Update();
		}
	}

	void KalaVideo::Shutdown()
	{
		UI_Core::Shutdown();

		cout << "[KALAKIT_VIDEO | DEBUG] Successfully shut down KalaVideo!\n";
	}
}