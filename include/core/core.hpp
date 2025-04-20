//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#pragma once

#ifdef KALAKIT_WINDOWS
#include <Windows.h>
#endif

namespace Core
{
	class KalaVideo
	{
	public:
		static void Initialize();
		static void Update();
		static void RedrawCallback();
		static void Shutdown();
	private:
#ifdef KALAKIT_WINDOWS
		static inline HDC hdc;
#endif
	};
}