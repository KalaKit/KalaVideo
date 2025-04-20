//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#pragma once

#include "platform.hpp"

namespace UI
{
	class UI_Core
	{
	public:
		static inline bool isInitialized;

		/// <summary>
		/// ImGui initialization.
		/// </summary>
		static void Initialize();

		static void SetStyle();

		static kvec2 CenterWindow(const kvec2& size);

		/// <summary>
		/// ImGui update loop.
		/// </summary>
		static void Update();

		/// <summary>
		/// Shut down ImGui.
		/// </summary>
		static void Shutdown();
	};
}