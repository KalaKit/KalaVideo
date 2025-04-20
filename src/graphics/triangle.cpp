//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#include <filesystem>
#include <string>
#include <iostream>

//external
#include "opengl_loader.hpp"
#include "platform.hpp"

//kalavideo
#include "graphics/triangle.hpp"

using std::filesystem::path;
using std::filesystem::current_path;
using std::string;
using std::cout;
using std::hex;
using std::make_unique;

using KalaKit::OpenGLLoader;

namespace Graphics
{
	void Triangle::Initialize()
	{
		float vertices[] =
		{
			 0.0f,  0.5f, //top
			-0.5f, -0.5f, //bottom left
			 0.5f, -0.5f  //bottom right
		};

		OpenGLLoader::glGenVertexArraysPtr(1, &vao);
		OpenGLLoader::glGenBuffersPtr(1, &vbo);

		OpenGLLoader::glBindVertexArrayPtr(vao);

		OpenGLLoader::glBindBufferPtr(GL_ARRAY_BUFFER, vbo);
		OpenGLLoader::glBufferDataPtr(
			GL_ARRAY_BUFFER, 
			sizeof(vertices), 
			vertices,
			GL_STATIC_DRAW);

		OpenGLLoader::glEnableVertexAttribArrayPtr(0);
		OpenGLLoader::glVertexAttribPointerPtr(
			0,
			2,
			GL_FLOAT,
			GL_FALSE,
			2 * sizeof(float),
			(void*)0);

		OpenGLLoader::glBindVertexArrayPtr(0);

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

		shader->SetVec4("u_Color", kvec4(1.0f, 0.0f, 0.0f, 1.0f));

		//bind the VAO
		OpenGLLoader::glBindVertexArrayPtr(vao);

		//draw the triangle
		OpenGLLoader::glDrawArraysPtr(GL_TRIANGLES, 0, 3);
	}
}