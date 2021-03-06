#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices){
	this->vertices = vertices;
	this->setupMesh();
}

void Mesh::Draw(Shader shader){
	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	glBindVertexArray(0);
}
void Mesh::DrawInstanced(Shader shader, std::vector<glm::mat4> modelMatrices){
	GLuint buffer;
	GLint amount = modelMatrices.size();

	glBindVertexArray(this->VAO);
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

	GLsizei vec4Size = sizeof(glm::vec4);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(vec4Size));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(2*vec4Size));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(3*vec4Size));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glDrawArraysInstanced(GL_TRIANGLES, 0, this->vertices.size(), amount);
	glBindVertexArray(0);

	glDeleteBuffers(1, &buffer);
}

Mesh::Mesh(){}

Mesh::~Mesh(){}

Mesh Mesh::GetPlaneMesh(){
	std::vector<Vertex> vertices;
	Vertex vertex;
	GLfloat points[] = {
		// Positions			// Normal      //TexCoords
		-0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,

		-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};
	for (GLuint i = 0; i < 6; i++)
	{
		vertex.Postion = glm::vec3(points[8 * i], points[8 * i + 1], points[8 * i + 2]);
		vertex.Normal = glm::vec3(points[8 * i + 3], points[8 * i + 4], points[8 * i + 5]);
		vertex.TexCoords = glm::vec2(points[8 * i + 6], points[8 * i + 7]);
		vertices.push_back(vertex);
	}
	return Mesh(vertices);
}

Mesh Mesh::GetCubeMesh(){
	std::vector<Vertex> vertices;
	Vertex vertex;
	GLfloat points[] = {
		//Back Face
		 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,

		//Front Face
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		//Left Face
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

		//Right Face
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

		//Bottom face
		 0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,

		//Top Face
		 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
	};
	for (GLuint i = 0; i < 36; i++)
	{
		vertex.Postion = glm::vec3(points[8 * i], points[8 * i + 1], points[8 * i + 2]);
		vertex.Normal = glm::vec3(points[8 * i + 3], points[8 * i + 4], points[8 * i + 5]);
		vertex.TexCoords = glm::vec2(points[8 * i + 6], points[8 * i + 7]);
		vertices.push_back(vertex);
	}

	return Mesh(vertices);
}

Mesh Mesh::GetSphereMesh(GLfloat radius){
	GLint division = int(64 * radius)/4 * 4;
	GLfloat angleStrip = 360.0f / division;

	std::vector<Vertex> vertices;
	Vertex vertex;
	glm::vec3 positions[4];
	glm::vec2 texCoords[4];
	GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

	GLfloat alpha;
	GLfloat beta;

	for (GLint y = 0; y < division / 2; y++){
		beta = (y - division / 4) * angleStrip;
		for (GLint x = 0; x < division; x++)
		{
			alpha = x * angleStrip;
			//bottom right
			positions[0] = calcPos(radius, alpha, beta);
			texCoords[0] = glm::vec2(GLfloat(x) / division, GLfloat(y) * 2.0 / division);
			//bottom left
			positions[1] = calcPos(radius, alpha + angleStrip, beta);
			texCoords[1] = glm::vec2(GLfloat(x + 1) / division, GLfloat(y) * 2.0 / division);
			//top left
			positions[2] = calcPos(radius, alpha + angleStrip, beta + angleStrip);
			texCoords[2] = glm::vec2(GLfloat(x + 1) / division, GLfloat(y + 1) * 2.0 / division);
			//top right
			positions[3] = calcPos(radius, alpha, beta + angleStrip);
			texCoords[3] = glm::vec2(GLfloat(x) / division, GLfloat(y + 1) * 2.0 / division);
			for (GLuint i = 0; i < 6; i++)
			{
				GLuint p = indices[i];
				vertex.Postion = positions[p];
				vertex.Normal = vertex.Postion;
				vertex.TexCoords = texCoords[p];
				vertices.push_back(vertex);
			}
		}
	}
	return Mesh(vertices);
}

void Mesh::setupMesh(){
	GLuint VBO;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
		&this->vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
}

glm::vec3 Mesh::calcPos(GLfloat radius, GLfloat alpha, GLfloat beta){
	glm::vec3 position;
	GLfloat rAlpha = glm::radians(alpha);
	GLfloat rBeta = glm::radians(beta);
	position.y = radius * glm::sin(rBeta);
	position.z = radius	* glm::cos(rBeta) * glm::sin(rAlpha);
	position.x = radius	* glm::cos(rBeta) * glm::cos(rAlpha);

	return position;
}