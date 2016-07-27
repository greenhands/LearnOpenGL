#ifndef PLANETOBJECT_H
#define PLANETOBJECT_H

#include "Common.h"
#include "SObject.h"

#include <vector>

class PlanetObject: public SObject
{
public:
	GLfloat T; //��ת����

	//�������
	GLfloat A; //�볤��
	GLfloat ��; //���������
	GLfloat I; //���ƫ��
	GLfloat ��; //���յ����
	GLfloat ��; //������ƾ�
	GLfloat M; //ƽ�����

	//��ת����
	GLfloat R; //�뾶
	GLfloat D; //��ת����
	GLfloat O; //��ת�����(obliguity)

	GLfloat ViewSize;
	//��������
	GLfloat Reflect; //������

	GLfloat Rotation; //��ת�Ƕ�
	glm::vec3 ViewDirection;
	glm::vec3 InitPos;

	PlanetObject();
	PlanetObject(Mesh *mesh, Texture2D *texture, std::vector<GLfloat> parameters);
	glm::vec3 CalcPostion(GLfloat time);
	void UpdatePosition(GLfloat time);
	void UpdateRotation(GLfloat time);
	void UpdateViewDirecton(PlanetObject *earth, GLfloat longitude, GLfloat latitude);
	void UpdateViewSize(PlanetObject *earth);
	void Draw(Shader shader);
	~PlanetObject();
private:
};

#endif