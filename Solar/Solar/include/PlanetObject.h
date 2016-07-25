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

	GLfloat Rotation; //��ת�Ƕ�

	PlanetObject();
	PlanetObject(Mesh *mesh, Texture2D *texture, std::vector<GLfloat> parameters);
	void UpdatePosition(GLfloat time);
	void UpdateRotation(GLfloat time);
	void Draw(Shader shader);
	~PlanetObject();
private:
};

#endif