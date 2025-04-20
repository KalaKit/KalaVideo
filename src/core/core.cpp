//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <string>

//external
#include "window.hpp"
#include "opengl.hpp"
#include "opengl_loader.hpp"
#include "enums.hpp"

//kalavideo
#include "core/core.hpp"
#include "graphics/triangle.hpp"
#include "ui/ui_core.hpp"

using std::cout;
using std::cin;
using std::filesystem::current_path;
using std::string;

using KalaKit::KalaWindow;
using KalaKit::OpenGL;
using KalaKit::OpenGLLoader;
using KalaKit::DebugType;
using KalaKit::PopupAction;
using KalaKit::PopupType;
using KalaKit::PopupResult;
using Graphics::Triangle;
using UI::UI_Core;

namespace Core
{
	void KalaVideo::Initialize()
	{
		//KalaWindow::SetDebugType(DebugType::DEBUG_FREETYPE_FONT_TEST);

		bool initializeOpenGL = true;
		bool initialized = KalaWindow::Initialize(
			"KalaVideo", 
			800, 
			600,
			initializeOpenGL);
		if (!initialized)
		{
			string message = "Failed to initialize KalaWindow!\n";
			cout << message;

			string title = "Initialize error";
			PopupAction action = PopupAction::POPUP_ACTION_OK;
			PopupType type = PopupType::POPUP_TYPE_ERROR;
			if (KalaWindow::CreatePopup(title, message, action, type)
				== PopupResult::POPUP_RESULT_OK)
			{
				KalaWindow::SetShouldCloseState(true);
				return;
			}
		}

		if (initializeOpenGL)
		{
			OpenGLLoader::glDisablePtr(GL_BLEND);      //no transparency
			OpenGLLoader::glDisablePtr(GL_CULL_FACE);  //don't discard faces
			OpenGLLoader::glDisablePtr(GL_DEPTH_TEST); //no depth test
	
			//Triangle::Initialize();
	
			KalaWindow::SetRedrawCallback(RedrawCallback);
		}

		UI_Core::Initialize();
	}
		
	void KalaVideo::Update()
	{
		cout << "[KALAKIT_VIDEO | DEBUG] Successfully reached render loop!\n";

		while (!KalaWindow::ShouldClose())
		{
			KalaWindow::Update();

			if (OpenGL::isInitialized) RedrawCallback();
		}
	}

	void KalaVideo::RedrawCallback()
	{
		OpenGLLoader::glClearColorPtr(0.1f, 0.1f, 0.1f, 1.0f); //dark gray
		OpenGLLoader::glClearPtr(GL_COLOR_BUFFER_BIT);

		//Triangle::Render();

		UI_Core::Update();

		KalaWindow::SwapOpenGLBuffers();
	}

	void KalaVideo::Shutdown()
	{
		UI_Core::Shutdown();

		cout << "[KALAKIT_VIDEO | DEBUG] Successfully shut down KalaVideo!\n";
	}
}