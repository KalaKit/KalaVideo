#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_Projection * u_Model * vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}
