//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#pragma once

#include "platform.hpp"

namespace UI
{
	class UI_Video
	{
	public:
		static inline int framebufferWidth;
		static inline int framebufferHeight;

		/// <summary>
		/// The main window that displays the video currently loaded into KalaVideo.
		/// </summary>
		static void DrawVideoWindow();
	private:
		static void DrawVideoWindowContent();
		static void UpdateFramebuffer(kvec2 renderSize);
	};
}