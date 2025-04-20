//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#ifdef KALAKIT_WINDOWS
#include <Windows.h>
#endif
#include <GL/GL.h>
#include <string>

//external
#include "platform.hpp"
#include "opengl_loader.hpp"
#include "window.hpp"

//kalavideo
#include "ui/ui_core.hpp"
#include "ui/ui_video.hpp"
#include "graphics/graphics_core.hpp"
#include "graphics/triangle.hpp"

using KalaKit::OpenGLLoader;
using KalaKit::DebugType;
using KalaKit::PopupAction;
using KalaKit::PopupType;
using KalaKit::PopupResult;
using KalaKit::KalaWindow;
using UI::UI_Core;
using UI::UI_Video;
using Graphics::Triangle;

using std::cout;
using std::string;

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
			OpenGLLoader::glDisable(GL_BLEND);      //no transparency
			OpenGLLoader::glDisable(GL_CULL_FACE);  //don't discard faces
			OpenGLLoader::glDisable(GL_DEPTH_TEST); //no depth test

			Graphics_Core::FramebufferSetup();
			Triangle::Initialize();

			KalaWindow::SetRedrawCallback(Graphics_Core::Update);
		}

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
		//render scene to framebuffer

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

		Triangle::Render();

		//render imgui to the default framebuffer

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
	}
}