#pragma once
#include "common/commonIncludes.h"

class GfTexture
{
public:
	GfTexture();
	~GfTexture();

	GLuint texture;
	GLuint texture_id;
	GLuint uvbuffer;
	std::vector<GLfloat> texture_uv;
private:

};

GfTexture::GfTexture()
{
}

GfTexture::~GfTexture()
{
}