//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#pragma once

#include <string>

namespace Video
{
	using std::string;

	class VideoPlayer
	{
	public:
		static void RenderVideoFrame(const string& video, unsigned int textureID);
	};
}