//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <filesystem>
#include <iostream>

//external
#include "stb_image.h"
#include "opengl_loader.hpp"

//kalavideo
#include "graphics/image.hpp"

using std::filesystem::exists;
using std::filesystem::path;
using std::filesystem::current_path;
using std::cout;

using KalaKit::OpenGLLoader;

namespace Graphics
{
	void Image::ImportImage(
		const string& imageName,
		const string& imagePath,
		kvec2 size,
		bool flip)
	{
		path imagesPath = path(current_path() / "files" / "icons");
		if (!exists(imagesPath))
		{
			cout << "Error: Failed to find images path from '" << imagePath << "'!\n";
			return;
		}

		if (images.contains(imageName))
		{
			cout << "Error: Image with name '" << imageName << "' has already been imported!\n";
			return;
		}

		string extension = path(imagePath).extension().string();
		if (extension != ".png"
			&& extension != ".jpg"
			&& extension != ".jpeg")
		{
			cout << "Error: File extension '" << extension << "' not supported for image importing!\n";
			return;
		}
		
		stbi_set_flip_vertically_on_load(flip ? 1 : 0);

		int width, height, channels;
		unsigned char* data = stbi_load(
			imagePath.c_str(),
			&width,
			&height,
			&channels,
			4
		);
		if (!data)
		{
			cout << "Error: Failed to import image '" << imageName << "'!\n";
			return;
		}

		GLuint tex{};
		OpenGLLoader::glGenTextures(1, &tex);
		OpenGLLoader::glBindTexture(GL_TEXTURE_2D, tex);
		OpenGLLoader::glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER,
			GL_LINEAR
		);
		OpenGLLoader::glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_MAG_FILTER,
			GL_LINEAR
		);
		OpenGLLoader::glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			data
		);
		OpenGLLoader::glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);

		images[imageName] = ImageFile
		{
			.textureID = tex,
			.width = static_cast<int>(size.x > 0 ? size.x : width),
			.height = static_cast<int>(size.y > 0 ? size.y : height)
		};

		cout << "Successfully imported image '" << imageName << "'!\n";
	}

	void Image::Shutdown()
	{
		if (images.size() > 0)
		{
			for (auto& [name, image] : images)
			{
				if (image.textureID != 0)
				{
					GLuint tex = static_cast<GLuint>(image.textureID);
					OpenGLLoader::glDeleteTextures(1, &tex);
				}
			}
			images.clear();

			cout << "Successfully deleted all images!\n";
		}
	}
}