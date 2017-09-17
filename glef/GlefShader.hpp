#pragma once
#include "common/commonIncludes.h"
#include "common/shader.hpp"

class GfShader {
private:
	GLuint shader_id;
public:
	/** Getter for shader id
	return Id of shader
	*/
	GLuint getId()
	{
		return shader_id;
	}
	GfShader() {};
	~GfShader()
	{
		glDeleteProgram(shader_id);
	}
	GfShader(GLuint shader_id)
	{
		this->shader_id = shader_id;
	}
};

class GfShaderFactory {
public:
	static GfShaderFactory& use()
	{
		static GfShaderFactory instance;
		return instance;
	}
	GfShaderFactory(GfShaderFactory const&) = delete;
	void operator=(GfShaderFactory const&) = delete;

	/** Loads shader from 2 files. One file store vertex shader, another- fragment shader
	@param vertexshader_file path to file with vertex shader
	@param fragmentshader_file path to file with fragment shader
	*/
	std::shared_ptr<GfShader> loadShader(std::string vertexshader_file, std::string fragmentshader_file)
	{
		GLuint id = LoadShaders(vertexshader_file.c_str(), fragmentshader_file.c_str());
		return std::make_shared<GfShader>(id);
	}
private:
	GfShaderFactory() {};
};