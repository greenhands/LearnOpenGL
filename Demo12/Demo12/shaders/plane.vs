#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

layout (std140) uniform Camera
{
	mat4 view;
	mat4 projection;
};

uniform mat4 model;

out vec3 Normal;
out vec2 TexCoords;

void main(){
	gl_Position = projection * view * model * vec4(position, 1.0);
	TexCoords = texCoords;
	Normal = normal;
}