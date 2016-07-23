#ifndef SOLARMATH_H
#define SOLARMATH_H

#include "Common.h"

class SolarMath
{
public:

	/*
	* �ÿ����չ�ʽ��������ƫ����ǣ��ǶȲ��û�����
	* M         : ƽ�����
	* Eccentric : ��Բ���������
	* error     : �������
	*/
	static GLfloat EccentricAnomaly(GLfloat M, GLfloat Eccentric, GLfloat error = 0.000001);

	/*
	* ����ƽ����Ǽ�������ʵ��ƫת�Ǻ���̫���ľ���
	* E			: ƫ�����
	* A			: ����볤��
	* Eccentric : ��Բ���������
	* r			: ����ֵ����ĵ�ַ
	* theta		: ����ֵʵ��ƫת�ǵĵ�ַ
	*/
	static void TrueAnomalyAndDistance(GLfloat E, GLfloat A, GLfloat Eccentric, GLfloat *r, GLfloat *theta);
	~SolarMath();
private:
	SolarMath();

};

#endif