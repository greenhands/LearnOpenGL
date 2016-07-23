#ifndef PLANETOBJECT_H
#define PLANETOBJECT_H

#include "Common.h"
#include "SObject.h"

class PlanetObject: public SObject
{
public:
	//�������
	GLfloat T; //��ת����
	GLfloat A; //�볤��
	GLfloat ��; //���������
	GLfloat I; //���ƫ��
	GLfloat ��; //���յ����
	GLfloat ��; //������ƾ�
	GLfloat M; //ƽ�����

	PlanetObject(glm::vec3 initPos, Mesh *mesh, Texture2D *texture);
	void UpdatePosition(GLfloat time);
	~PlanetObject();

private:
};

#endif