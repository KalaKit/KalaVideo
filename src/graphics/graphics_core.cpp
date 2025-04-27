//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#ifdef KALAKIT_WINDOWS
#include <Windows.h>
#endif
#include <GL/GL.h>
#include <string>
#include <iostream>
#include <filesystem>

//external
#include "opengl_loader.hpp"
#include "window.hpp"

//kalavideo
#include "ui/ui_core.hpp"
#include "ui/ui_video.hpp"
#include "graphics/graphics_core.hpp"
#include "graphics/triangle.hpp"
#include "video/video_player.hpp"
#include "video/video_import.hpp"
#include "graphics/quad.hpp"
#include "graphics/image.hpp"

using std::string;
using std::cout;
using std::filesystem::path;
using std::filesystem::current_path;

using KalaKit::OpenGLLoader;
using KalaKit::DebugType;
using KalaKit::PopupAction;
using KalaKit::PopupType;
using KalaKit::PopupResult;
using KalaKit::KalaWindow;
using UI::UI_Core;
using UI::UI_Video;
using Graphics::Triangle;
using Graphics::Image;
using Video::VideoPlayer;
using Video::VideoImport;

namespace Graphics
{
	void Graphics_Core::Initialize()
	{
		bool initializeOpenGL = true;
		bool initialized = KalaWindow::Initialize(
			"KalaVideo",
			800,
			600,
			initializeOpenGL);
		if (!initialized)
		{
			string message = "Failed to initialize KalaWindow!\n";
			
			cout << message << "\n";

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
			//OpenGLLoader::glDisable(GL_BLEND);      //no transparency
			//OpenGLLoader::glDisable(GL_CULL_FACE);  //don't discard faces
			//OpenGLLoader::glDisable(GL_DEPTH_TEST); //no depth test

			Graphics_Core::FramebufferSetup();

			KalaWindow::SetRedrawCallback(Graphics_Core::Update);
		}

		path imagesPath = path(current_path() / "files" / "icons");
		string icon_play = path(imagesPath / "icon_play.png").string();
		string icon_pause = path(imagesPath / "icon_pause.png").string();
		string icon_stop = path(imagesPath / "icon_stop.png").string();
		string icon_restart = path(imagesPath / "icon_restart.png").string();
		kvec2 size = kvec2(35.0f, 35.0f);

		Image::ImportImage("icon_play", icon_play, size);
		Image::ImportImage("icon_pause", icon_pause, size);
		Image::ImportImage("icon_stop", icon_stop, size);
		Image::ImportImage("icon_restart", icon_restart, size);

		UI_Core::Initialize();
	}

	void Graphics_Core::FramebufferSetup()
	{
		//set up framebuffer
		OpenGLLoader::glGenFramebuffers(1, &framebuffer);
		OpenGLLoader::glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		//set up color attachment texture
		OpenGLLoader::glGenTextures(1, &textureColorBuffer);
		OpenGLLoader::glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
		OpenGLLoader::glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			1024,
			768,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			NULL);
		OpenGLLoader::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		OpenGLLoader::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		OpenGLLoader::glFramebufferTexture2D(
			GL_FRAMEBUFFER,
			GL_COLOR_ATTACHMENT0,
			GL_TEXTURE_2D,
			textureColorBuffer,
			0);

		//set up renderbuffer object 
		//for depth and stencil attachment
		OpenGLLoader::glGenRenderbuffers(1, &rbo);
		OpenGLLoader::glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		OpenGLLoader::glRenderbufferStorage(
			GL_RENDERBUFFER,
			GL_DEPTH24_STENCIL8,
			1024,
			768);
		OpenGLLoader::glFramebufferRenderbuffer(
			GL_FRAMEBUFFER,
			GL_DEPTH_STENCIL_ATTACHMENT,
			GL_RENDERBUFFER,
			rbo);

		if (OpenGLLoader::glCheckFramebufferStatus(GL_FRAMEBUFFER) 
			!= GL_FRAMEBUFFER_COMPLETE)
		{
			cout << "Error: Framebuffer is not complete!\n";
			return;
		}
		OpenGLLoader::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Graphics_Core::Update()
	{
		//
		// RENDER SCENE TO FRAMEBUFFER
		//

		OpenGLLoader::glBindFramebuffer(
			GL_FRAMEBUFFER,
			Graphics_Core::framebuffer
		);
		OpenGLLoader::glViewport(
			0,
			0,
			UI_Video::framebufferWidth,
			UI_Video::framebufferHeight
		);
		OpenGLLoader::glClearColor(0.1f, 0.1f, 0.1f, 1.0f); //dark gray
		OpenGLLoader::glClear(
			GL_COLOR_BUFFER_BIT
			| GL_DEPTH_BUFFER_BIT
		);

		//
		// RENDER THE VIDEO QUAD
		//

		if (reachedFirstFrameEnd)
		{
			if (!isQuadInitialized)
			{
				Quad::Initialize();
				isQuadInitialized = true;
			}

			static string firstVideo = "";
			if (!VideoImport::importedVideos.empty())
			{
				if (firstVideo == "")
				{
					firstVideo = VideoImport::importedVideos.begin()->first;
					cout << "Assigned '" << firstVideo << "' as playback video.\n";
				}

				VideoPlayer::RenderVideoFrame(firstVideo, Quad::textureID);
				Quad::Render();
			}
		}

		//
		// RENDER IMGUI TO THE DEFAULT FRAMEBUFFER
		//

		OpenGLLoader::glBindFramebuffer(
			GL_FRAMEBUFFER,
			0
		);
		OpenGLLoader::glViewport(
			0,
			0,
			KalaWindow::GetWindowContentSize().x,
			KalaWindow::GetWindowContentSize().y
		);
		UI_Core::Update();

		KalaWindow::SwapOpenGLBuffers();

		if (!reachedFirstFrameEnd) reachedFirstFrameEnd = true;
	}
}