#pragma once
//Standart libs
#include "common/commonIncludes.h"

//Glef libs
#include "GlefCollor.hpp"
#include "GlefWindow.hpp"
#include "GlefEnums.hpp"
#include "GlefShader.hpp"
#include "GlefObject.hpp"



#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

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
		if (is_textured) {
			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture);
			// Set our "myTextureSampler" sampler to use Texture Unit 0
			glUniform1i(texture_id, 0);
		}
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
		if (!is_textured) {
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
		}
		else
		{
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
			glVertexAttribPointer(
				1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				2,                                // size : U+V => 2
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);
		}
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

	void addTexture(std::string texture, std::vector<GLfloat> uv)
	{
		this->Texture = loadDDS("uvtemplate.DDS");
		this->texture_id= glGetUniformLocation(shader->getId(), "Texture");
		this->texture_uv = uv;
		is_textured = true;

		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, uv.size()* sizeof(GLfloat), reinterpret_cast<void*>(uv.data()), GL_STATIC_DRAW);
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

	std::vector<GLfloat> texture_uv;
	GLuint Texture;
	GLuint texture_id;
	GLuint uvbuffer;
	bool is_textured = 0;
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



	GLuint loadDDS(const char * imagepath) {

		unsigned char header[124];

		FILE *fp;

		/* try to open the file */
		fp = fopen(imagepath, "rb");
		if (fp == NULL) {
			printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar();
			return 0;
		}

		/* verify the type of file */
		char filecode[4];
		fread(filecode, 1, 4, fp);
		if (strncmp(filecode, "DDS ", 4) != 0) {
			fclose(fp);
			return 0;
		}

		/* get the surface desc */
		fread(&header, 124, 1, fp);

		unsigned int height = *(unsigned int*)&(header[8]);
		unsigned int width = *(unsigned int*)&(header[12]);
		unsigned int linearSize = *(unsigned int*)&(header[16]);
		unsigned int mipMapCount = *(unsigned int*)&(header[24]);
		unsigned int fourCC = *(unsigned int*)&(header[80]);


		unsigned char * buffer;
		unsigned int bufsize;
		/* how big is it going to be including all mipmaps? */
		bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
		buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
		fread(buffer, 1, bufsize, fp);
		/* close the file pointer */
		fclose(fp);

		unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
		unsigned int format;
		switch (fourCC)
		{
		case FOURCC_DXT1:
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FOURCC_DXT3:
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			break;
		case FOURCC_DXT5:
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		default:
			free(buffer);
			return 0;
		}

		// Create one OpenGL texture
		GLuint textureID;
		glGenTextures(1, &textureID);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, textureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
		unsigned int offset = 0;

		/* load the mipmaps */
		for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
		{
			unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
				0, size, buffer + offset);

			offset += size;
			width /= 2;
			height /= 2;

			// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
			if (width < 1) width = 1;
			if (height < 1) height = 1;

		}

		free(buffer);

		return textureID;


	}
};