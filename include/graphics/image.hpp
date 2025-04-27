//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#pragma once

#include <unordered_map>
#include <string>

//external
#include "platform.hpp"

namespace Graphics
{
	using std::unordered_map;
	using std::string;

	struct ImageFile
	{
		unsigned int textureID;
		int width;
		int height;
	};

	class Image
	{
	public:
		static inline unordered_map<string, ImageFile> images;

		/// <summary>
		/// Import image with chosen name from path. 
		/// Also alternatively assign a size to it, 
		/// and if it should be flipped or not.
		/// </summary>
		static void ImportImage(
			const string& name, 
			const string& path,
			kvec2 size = kvec2{0, 0},
			bool flip = false);

		static void Shutdown();
	};
}