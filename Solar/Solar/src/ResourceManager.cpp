#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;
std::map<std::string, Mesh> ResourceManager::Meshes;

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name){
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}
Shader ResourceManager::GetShader(std::string name){
	return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name){
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}
Texture2D ResourceManager::GetTexture(std::string name){
	return Textures[name];
}

Mesh ResourceManager::StoreMesh(Mesh mesh, std::string name){
	Meshes[name] = mesh;
	return Meshes[name];
}

Mesh ResourceManager::GetMesh(std::string name){
	return Meshes[name];
}


void ResourceManager::Clear(){
	for (auto iter : Shaders)
	{
		glDeleteProgram(iter.second.ID);
	}
	for (auto iter : Textures)
	{
		glDeleteTextures(1, &iter.second.ID);
	}
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile){
	std::string vertexCode, fragmentCode, geometryCode;

	try
	{
		std::ifstream vertexFile(vShaderFile);
		std::ifstream fragmentFile(fShaderFile);

		std::stringstream vertexString, fragmentString;

		vertexString << vertexFile.rdbuf();
		fragmentString << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexString.str();
		fragmentCode = fragmentString.str();

		if (gShaderFile != nullptr)
		{
			std::ifstream geometryFile(gShaderFile);
			std::stringstream geometryString;
			geometryString << geometryFile.rdbuf();
			geometryFile.close();
			geometryCode = geometryString.str();
		}
	}
	catch (std::exception* e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();

	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha){
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}

	int width, height;
	unsigned char *image = SOIL_load_image(file, &width, &height, 0, texture.Internal_Format != GL_RGBA ? SOIL_LOAD_RGB : SOIL_LOAD_RGBA);
	texture.Generate(width, height, image);
	return texture;
}