//Copyright(C) 2025 Lost Empire Entertainment
//This program comes with ABSOLUTELY NO WARRANTY.
//This is free software, and you are welcome to redistribute it under certain conditions.
//Read LICENSE.md for more information.

#pragma once

#include <memory>

//external
#include "platform.hpp"
#include "shader.hpp"

namespace Graphics
{
	using std::unique_ptr;

	using KalaKit::Shader;

	class Quad
	{
	public:
		static inline unsigned int VAO;
		static inline unsigned int VBO;
		static inline unsigned int textureID;
		static inline unique_ptr<Shader> shader;

		static kmat4 Orthographic(
			float left,
			float right,
			float bottom,
			float top,
			float nearZ,
			float farZ);

		static void Initialize();
		static void Render();
	private:
		static kmat4 Translate(const kmat4& matrix, const kvec3& position);
		static kmat4 Scale(const kmat4& matrix, const kvec3& scale);
	};
}