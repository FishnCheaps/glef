#pragma once
//Standart libs
#include "common/commonIncludes.h"

//Glef libs
#include "GlefCollor.hpp"
#include "GlefWindow.hpp"
#include "GlefEnums.hpp"
#include "GlefShader.hpp"
#include "GlefObject.hpp"
#include "GlefTexture.hpp"
#include "GlefCamera.hpp"
#include "GlefWindow.hpp"



#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

using namespace glm;

//void computeCameraMatricesFromInputs(GfCameraActive * camera, GfWindow * window, GfControls * controls) {
//
//	// glfwGetTime is called only once, the first time this function is called
//	static double lastTime = glfwGetTime();
//
//	// Compute time difference between current and last frame
//	double currentTime = glfwGetTime();
//	float deltaTime = float(currentTime - lastTime);
//
//	// Get mouse position
//	double xpos, ypos;
//	//glfwGetCursorPos(window->window_ptr, &xpos, &ypos);
//	// Reset mouse position for next frame
//	//glfwSetCursorPos(window->window_ptr, window->width / 2, window->height / 2);
//	//glfwSetCursorPos(window->window_ptr, 1024 / 2, 768 / 2);
//	// Compute new orientation
//	//camera->horizontal_angle = controls->mouseSpeed* float(window->width / 2 - xpos);
//	//camera->vertical_angle = controls->mouseSpeed* float(window->height / 2 - ypos);
//	//camera->horizontal_angle += controls->mouseSpeed* float(1024 / 2 - xpos);
//	//camera->vertical_angle += controls->mouseSpeed* float(768 / 2 - ypos);
//	//::cout << camera->horizontal_angle << " " << camera->vertical_angle << std::endl;
//	// Direction : Spherical coordinates to Cartesian coordinates conversion
//	glm::vec3 direction(
//		cos(camera->vertical_angle) * sin(camera->horizontal_angle),
//		sin(camera->vertical_angle),
//		cos(camera->vertical_angle) * cos(camera->horizontal_angle)
//	);
//
//	// Right vector
//	glm::vec3 right = glm::vec3(
//		sin(camera->horizontal_angle - 3.14f / 2.0f),
//		0,
//		cos(camera->horizontal_angle - 3.14f / 2.0f)
//	);
//
//	// Up vector
//	glm::vec3 up = glm::cross(right, direction);
//
//	// Move forward
//	if (glfwGetKey(window->window_ptr, controls->key_up) == GLFW_PRESS) {
//		camera->position += direction * deltaTime * controls->speed;
//	}
//	// Move backward
//	if (glfwGetKey(window->window_ptr, controls->key_down) == GLFW_PRESS) {
//		camera->position -= direction * deltaTime * controls->speed;
//	}
//	// Strafe right
//	if (glfwGetKey(window->window_ptr, controls->key_right) == GLFW_PRESS) {
//		camera->position += right * deltaTime * controls->speed;
//	}
//	// Strafe left
//	if (glfwGetKey(window->window_ptr, controls->key_left) == GLFW_PRESS) {
//		camera->position -= right * deltaTime * controls->speed;
//	}
//
//	float FoV = camera->initial_fov;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.
//
//									// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//	camera->projection_matrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
//	// Camera matrix
//	camera->view_matrix = glm::lookAt(
//		camera->position,           // Camera is here
//		camera->position + direction, // and looks here : at the same position, plus "direction"
//		up                  // Head is up (set to 0,-1,0 to look upside-down)
//	);
//
//	// For the next frame, the "last time" will be "now"
//	lastTime = currentTime;
//}



class GfModel : public GfObject
{
public:
	//refactor
	GfShader* shader;
	GLuint vbo;
	GLuint vao;
	GLuint matrix_id;
	GLuint ModelMatrixID;
	GLuint color;
	GLuint normal;
	bool is_textured = 0;
	bool is_normals_set = 0;
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> colors;
	std::vector<GLfloat> texture_uv;
	std::vector<glm::vec3> normals;
	GfTexture textureFromModelTMP() //TO-DO remove it
	{
		GfTexture tx;
		tx.texture = this->Texture;
		tx.texture_id = this->texture_id;
		tx.texture_uv = this->texture_uv;
		tx.uvbuffer = this->uvbuffer;
		return tx;
	}

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
	void setNormals(std::vector<glm::vec3> new_normals)
	{
		if (!is_normals_set)
			genNormals();
		normals = new_normals;
		glBindBuffer(GL_ARRAY_BUFFER, normal);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), reinterpret_cast<void*>(normals.data()), GL_STATIC_DRAW);
	}
	/** Proceed this element in every frame. Drowing object
	@param shaders Shader that should be used for drowing model
	*/
	void useElement(GfCameraActive * cam, GfWindow * window)
	{
		glUseProgram(shader->getId());
		//tmp
		//computeCameraMatricesFromInputs(cam, window, &(cam->controls));
		glm::mat4 ProjectionMatrix = cam->projection_matrix;
		glm::mat4 ViewMatrix = cam->view_matrix;
		glm::mat4 ModelMatrix = model_matrix;                    //!!!!!!
		mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;
		//tmp
		glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(cam->ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
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
		if (is_normals_set)
		{
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, normal);
			glVertexAttribPointer(
				2,                                // attribute
				3,                                // size
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
		if (is_normals_set)
			glDisableVertexAttribArray(2);
	}
	void postInit() override
	{
		matrix_id = glGetUniformLocation(shader->getId(), "mvp");
		ModelMatrixID= glGetUniformLocation(shader->getId(), "M");
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
	bool is_vbo_set = 0;
	bool is_vao_set = 0;
	bool is_color_set = 0;
	GLuint Texture;
	GLuint texture_id;
	GLuint uvbuffer;
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
	void genNormals()
	{
		glGenBuffers(1, &normal);
		is_normals_set = true;
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



