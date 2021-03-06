#include "Texture2D.h"

Texture2D::Texture2D()
	:width(0), height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), DataType(GL_UNSIGNED_BYTE),
	Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Mag(GL_LINEAR)
{
}

Texture2D::~Texture2D(){}

void Texture2D::Generate(GLuint width, GLuint height, unsigned char *data){
	glGenTextures(1, &this->ID);
	this->width = width;
	this->height = height;
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, this->width, this->height, 0, this->Image_Format, this->DataType, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Mag);

	if (this->Wrap_S == GL_CLAMP_TO_BORDER)
	{
		GLfloat borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}