#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture0;

void main(){
	vec4 texColor = texture(texture0, TexCoords);
	color = texColor;
}