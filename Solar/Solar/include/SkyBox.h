#ifndef SKYBOX_H
#define SKYBOX_H

#include "Common.h"
#include "Shader.h"
#include "TextureCube.h"
#include "Mesh.h"

class SkyBox
{
public:
	glm::vec3 Position;
	GLfloat Size;
	GLfloat Brightness;

	Mesh *mesh;
	TextureCube *cubeMap;

	SkyBox();
	SkyBox(Mesh *mesh, TextureCube *cubeMap);
	void UpdateBrightness(glm::vec3 sunPos);
	void Draw(Shader shader);
	~SkyBox();

private:

};

#endif