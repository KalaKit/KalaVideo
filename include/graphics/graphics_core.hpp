//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#pragma once

namespace Graphics
{
	class Graphics_Core
	{
	public:
		static inline unsigned int framebuffer;
		static inline unsigned int textureColorBuffer;
		static inline unsigned int rbo;

		static void Initialize();
		static void Update();

	private:
		static void FramebufferSetup();
	};
}