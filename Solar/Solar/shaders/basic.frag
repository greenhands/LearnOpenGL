#version 330 core
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D diffuse;
uniform sampler2D specular;

out vec4 color;

void main(){
	color = vec4(texture(diffuse, TexCoords));
}