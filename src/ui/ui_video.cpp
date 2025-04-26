//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <iostream>

//external
#include "imgui.h"
#include "opengl_loader.hpp"

//kalavideo
#include "ui/ui_video.hpp"
#include "ui/ui_core.hpp"
#include "graphics/graphics_core.hpp"

using std::cout;

using Graphics::Graphics_Core;
using KalaKit::OpenGLLoader;

namespace UI
{
	static ImVec2 windowMinSize = ImVec2(300, 300);
	static ImVec2 windowMaxSize = ImVec2(FLT_MAX, FLT_MAX);

	void UI_Video::DrawVideoWindow()
	{
		ImGui::SetNextWindowSizeConstraints(
			windowMinSize,
			windowMaxSize);

		ImVec2 size = ImGui::GetMainViewport()->Size;
		float targetHeight = size.y * 0.85f;
		ImGui::SetNextWindowSize(
			ImVec2(size.x, targetHeight),
			ImGuiCond_Always);
		ImGui::SetNextWindowPos(
			ImVec2(0, 22),
			ImGuiCond_Always);

		ImGuiWindowFlags winFlags =
			ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoSavedSettings
			| ImGuiWindowFlags_NoTitleBar;

		if (ImGui::Begin("Video", nullptr, winFlags))
		{
			DrawVideoWindowContent();
			ImGui::End();
		}
	}

	void UI_Video::DrawVideoWindowContent()
	{
		ImVec2 contentRegionMin = ImGui::GetWindowContentRegionMin();
		ImVec2 contentRegionMax = ImGui::GetWindowContentRegionMax();
		ImVec2 availableSize = ImVec2(
			contentRegionMax.x - contentRegionMin.x,
			contentRegionMax.y - contentRegionMin.y);

		float windowAspectRatio = availableSize.x / availableSize.y;
		float targetAspectRatio = 16.0f / 9.0f;

		ImVec2 renderSize = availableSize;
		if (windowAspectRatio > targetAspectRatio)
		{
			renderSize.x = availableSize.y * targetAspectRatio;
		}
		else
		{
			renderSize.y = availableSize.x / targetAspectRatio;
		}

		renderSize.x = roundf(renderSize.x);
		renderSize.y = roundf(renderSize.y);

		ImVec2 padding(
			(availableSize.x - renderSize.x) * 0.5f,
			(availableSize.y - renderSize.y) * 0.5f);
		ImGui::SetCursorPos(ImVec2(
			contentRegionMin.x + padding.x,
			contentRegionMin.y + padding.y));

		if (renderSize.x != framebufferWidth
			|| renderSize.y != framebufferHeight)
		{
			UpdateFramebuffer(kvec2(renderSize.x, renderSize.y));
		}

		ImGui::Image(
			Graphics_Core::textureColorBuffer,
			renderSize,
			ImVec2(0, 1),
			ImVec2(1, 0));
	}

	void UI_Video::UpdateFramebuffer(kvec2 renderSize)
	{
		framebufferWidth = static_cast<int>(renderSize.x);
		framebufferHeight = static_cast<int>(renderSize.y);

		OpenGLLoader::glBindTexture(
			GL_TEXTURE_2D,
			Graphics_Core::textureColorBuffer
		);
		OpenGLLoader::glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			framebufferWidth,
			framebufferHeight,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			NULL
		);

		OpenGLLoader::glBindRenderbuffer(
			GL_RENDERBUFFER,
			Graphics_Core::rbo
		);
		OpenGLLoader::glRenderbufferStorage(
			GL_RENDERBUFFER,
			GL_DEPTH24_STENCIL8,
			framebufferWidth,
			framebufferHeight
		);

		OpenGLLoader::glBindFramebuffer(GL_FRAMEBUFFER, Graphics_Core::framebuffer);
		OpenGLLoader::glViewport(0, 0, framebufferWidth, framebufferHeight);
		OpenGLLoader::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		OpenGLLoader::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		OpenGLLoader::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}