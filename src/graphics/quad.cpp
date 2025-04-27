//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <string>
#include <filesystem>
#include <iostream>

//external
#include "opengl_loader.hpp"

//kalavideo
#include "graphics/quad.hpp"
#include "ui/ui_video.hpp"

using std::string;
using std::filesystem::current_path;
using std::cout;

using KalaKit::OpenGLLoader;
using UI::UI_Video;

namespace Graphics
{
	kmat4 Quad::Orthographic(
		float left,
		float right,
		float bottom,
		float top,
		float nearZ,
		float farZ
	)
	{
		kmat4 result{};

		float rl = right - left;
		float tb = top - bottom;
		float fn = farZ - nearZ;

		result.columns[0] = kvec4(
			2.0f / rl,
			0.0f,
			0.0f,
			0.0f
		);
		result.columns[1] = kvec4(
			0.0f,
			2.0f / tb,
			0.0f,
			0.0f
		);
		result.columns[2] = kvec4(
			0.0f,
			0.0f,
			-2.0f / fn,
			0.0f
		);
		result.columns[3] = kvec4(
			-(right + left) / rl,
			-(top + bottom) / tb,
			-(farZ + nearZ) / fn,
			1.0f
		);

		return result;
	}

	void Quad::Initialize()
	{
		//full screen 1x1 quad (unit quad)
		float vertices[] = 
		{
			//pos      //texcoord
			0.0f, 0.0f, 0.0f, 0.0f, //top-left
			1.0f, 0.0f, 1.0f, 0.0f, //top-right
			1.0f, 1.0f, 1.0f, 1.0f, //bottom-right
			0.0f, 1.0f, 0.0f, 1.0f  //bottom-left
		};

		OpenGLLoader::glGenVertexArrays(1, &VAO);
		OpenGLLoader::glGenBuffers(1, &VBO);

		OpenGLLoader::glBindVertexArray(VAO);

		OpenGLLoader::glBindBuffer(GL_ARRAY_BUFFER, VBO);
		OpenGLLoader::glBufferData(
			GL_ARRAY_BUFFER, 
			sizeof(vertices), 
			vertices, 
			GL_STATIC_DRAW);

		//position attribute
		OpenGLLoader::glEnableVertexAttribArray(0);
		OpenGLLoader::glVertexAttribPointer(
			0, 
			2, 
			GL_FLOAT, 
			GL_FALSE, 
			4 * sizeof(float),
			(void*)0);

		//texCoord attribute
		OpenGLLoader::glEnableVertexAttribArray(1);
		OpenGLLoader::glVertexAttribPointer(
			1, 
			2,
			GL_FLOAT,
			GL_FALSE,
			4 * sizeof(float),
			(void*)(2 * sizeof(float)));

		OpenGLLoader::glBindVertexArray(0);

		//create shader
		string vert = (current_path() / "files" / "shaders" / "quad.vert").string();
		string frag = (current_path() / "files" / "shaders" / "quad.frag").string();

		shader = make_unique<Shader>(vert, frag);

		if (!shader->IsValid())
		{
			cout << "Error: Quad shader failed to compile/link!\n";
		}

		shader->Use();
		shader->SetInt("u_Texture", 0);

		//create the texture
		OpenGLLoader::glGenTextures(1, &textureID);
		OpenGLLoader::glBindTexture(GL_TEXTURE_2D, textureID);
		OpenGLLoader::glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			1,
			1,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			nullptr
		);

		//set sampler parameters
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
		OpenGLLoader::glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_WRAP_S,
			GL_CLAMP_TO_EDGE
		);
		OpenGLLoader::glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_WRAP_T,
			GL_CLAMP_TO_EDGE
		);

		OpenGLLoader::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		OpenGLLoader::glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 3);
		OpenGLLoader::glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Quad::Render()
	{
		//use the compiled shader program
		shader->Use();

		kmat4 projection = Orthographic(
			0.0f,
			static_cast<float>(UI_Video::framebufferWidth),
			static_cast<float>(UI_Video::framebufferHeight),
			0.0f,
			-1.0f,
			1.0f
		);
		shader->SetMat4("u_Projection", projection);

		kmat4 model{};
		model.columns[0].x = 1.0f;
		model.columns[1].y = 1.0f;
		model.columns[2].z = 1.0f;
		model.columns[3].w = 1.0f;

		model = Translate(model, kvec3(0.0f, 0.0f, 0.0f));
		model = Quad::Scale(
			model, 
			kvec3(
				static_cast<float>(UI_Video::framebufferWidth),
				static_cast<float>(UI_Video::framebufferHeight),
				1.0f)
		);

		shader->SetMat4("u_Model", model);

		OpenGLLoader::glActiveTexture(GL_TEXTURE0); //activate texture unit 0
		OpenGLLoader::glBindTexture(GL_TEXTURE_2D, textureID);

		//bind the VAO
		OpenGLLoader::glBindVertexArray(VAO);

		//draw the full screen quad
		OpenGLLoader::glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}

	kmat4 Quad::Translate(const kmat4& matrix, const kvec3& pos)
	{
		kmat4 result = matrix;

		result.columns[3].x += pos.x;
		result.columns[3].y += pos.y;
		result.columns[3].z += pos.z;

		return result;
	}

	kmat4 Quad::Scale(const kmat4& matrix, const kvec3& scale)
	{
		kmat4 result = matrix;

		result.columns[0].x *= scale.x;
		result.columns[1].y *= scale.y;
		result.columns[2].z *= scale.z;

		return result;
	}
}