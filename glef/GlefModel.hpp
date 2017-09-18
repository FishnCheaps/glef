#pragma once
//Standart libs
#include "common/commonIncludes.h"

//Glef libs
#include "GlefCollor.hpp"
#include "GlefWindow.hpp"
#include "GlefEnums.hpp"
#include "GlefShader.hpp"
#include "GlefObject.hpp"
using namespace glm;

class GfModel : public GfObject
{
public:
	//GfModel() {};
	~GfModel()
	{
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &color);
	}
	void setVertices(std::vector<GLfloat> new_vertices)
	{
		if (!is_vao_set)
			genVAO();
		glBindVertexArray(vao);

		vertices = new_vertices;

		if (!is_vbo_set)
			genVBO();
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), reinterpret_cast<void*>(vertices.data()), GL_STATIC_DRAW); //TO_DO set GL_DYNAMIC_DROW if obj rewriten
	}
	void setColor(std::vector<GLfloat> new_color)
	{
		if (!is_color_set)
			genCollor();
		colors = new_color;
		glBindBuffer(GL_ARRAY_BUFFER, color);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), reinterpret_cast<void*>(colors.data()), GL_STATIC_DRAW);
	}
	/** Proceed this element in every frame. Drowing object
	@param shaders Shader that should be used for drowing model
	*/
	void useElement() override
	{
		glUseProgram(shader->getId());
		glUniformMatrix4fv(matrix, 1, GL_FALSE, &mvp[0][0]);
		glEnableVertexAttribArray(0); //TO-DO Ask Alehondrii
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, color);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);//TO-DO Ask Alehondrii
		glDisableVertexAttribArray(1);
	}
	void postInit() override
	{
		matrix = glGetUniformLocation(shader->getId(), "mvp");
	}
	/** Set shader for model
	@param mesh_vertices pointer on a shader
	*/
	void setShader(GfShader* shader)
	{
		this->shader = shader;
	}
private:
	GfShader* shader;
	GLuint vbo;
	GLuint vao;
	GLuint matrix;
	GLuint color;
	bool is_vbo_set = 0;
	bool is_vao_set = 0;
	bool is_color_set = 0;
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> colors;
	/** Generate VAO array and store its handler in vao field
	*/
	void genVAO()
	{
	

		glGenVertexArrays(1, &vao);
		is_vao_set = true;
	}
	/** Generate VBO array and store its handler in vbo field
	*/
	void genVBO()
	{
		glGenBuffers(1, &vbo);
		is_vbo_set = true;
	}
	/** Generate collor array and store its handler in vbo field
	*/
	void genCollor()
	{
		glGenBuffers(1, &color);
		is_color_set = true;
	}
};