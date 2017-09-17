#pragma once
//Standart libs
#include <iostream>
#include <vector>
#include <string>

//GL libs
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <common/shader.hpp>

//Glef libs
#include "GlefCollor.hpp"
#include "GlefWindow.hpp"
#include "GlefEnums.hpp"
using namespace glm;

class GfModel {
public:
	//GfModel() {};
	~GfModel()
	{
		glDeleteBuffers(1, &vbo);
		glDeleteVertexArrays(1, &vao);
		glDeleteProgram(shaders);
	}
	/** Load shaders for model
	@param vertex_shader Path to file with vertex shader
	@param vertex_shader Path to file with fragment shader
	*/
	void loadShaders(std::string vertex_shader,std::string fragment_shader)
	{
		shaders=LoadShaders(vertex_shader.c_str(), fragment_shader.c_str());
	}
	void set_vertices(std::vector<GLfloat> new_vertices)
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
	/** Proceed this element in every frame. Drowing object
	*/
	void useElement()
	{
		glUseProgram(shaders);
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

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);//TO-DO Ask Alehondrii
	}
private:
	GLuint shaders;
	GLuint vbo;
	GLuint vao;
	bool is_vbo_set = 0;
	bool is_vao_set = 0;
	std::vector<GLfloat> vertices;
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
};