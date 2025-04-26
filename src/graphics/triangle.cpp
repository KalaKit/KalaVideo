//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <filesystem>
#include <string>
#include <iostream>

//external
#include "opengl_loader.hpp"

//kalavideo
#include "graphics/triangle.hpp"
#include "ui/ui_video.hpp"

using KalaKit::OpenGLLoader;
using UI::UI_Video;

using std::filesystem::path;
using std::filesystem::current_path;
using std::string;
using std::hex;
using std::make_unique;
using std::cout;

namespace Graphics
{
	kmat4 Triangle::Orthographic(
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

	void Triangle::Initialize()
	{
		float vertices[] = 
		{
			300.0f, 100.0f,  // top
			200.0f, 300.0f,  // bottom left
			400.0f, 300.0f   // bottom right
		};

		OpenGLLoader::glGenVertexArrays(1, &vao);
		OpenGLLoader::glGenBuffers(1, &vbo);

		OpenGLLoader::glBindVertexArray(vao);

		OpenGLLoader::glBindBuffer(GL_ARRAY_BUFFER, vbo);
		OpenGLLoader::glBufferData(
			GL_ARRAY_BUFFER, 
			sizeof(vertices), 
			vertices,
			GL_STATIC_DRAW);

		OpenGLLoader::glEnableVertexAttribArray(0);
		OpenGLLoader::glVertexAttribPointer(
			0,
			2,
			GL_FLOAT,
			GL_FALSE,
			2 * sizeof(float),
			(void*)0);

		OpenGLLoader::glBindVertexArray(0);

		//create shader
		string vert = (current_path() / "files" / "shaders" / "tri.vert").string();
		string frag = (current_path() / "files" / "shaders" / "tri.frag").string();
		
		shader = make_unique<Shader>(vert, frag);

		if (!shader->IsValid())
		{
			cout << "Error: Triangle shader failed to compile/link!\n";
		}
	}

	void Triangle::Render()
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
		shader->SetVec4("u_Color", kvec4(1.0f, 0.0f, 0.0f, 1.0f));

		//bind the VAO
		OpenGLLoader::glBindVertexArray(vao);

		//draw the triangle
		OpenGLLoader::glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}