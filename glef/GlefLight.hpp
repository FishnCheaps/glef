#pragma once
#include "common/commonIncludes.h"
#include "GlefObject.hpp"
#include "GlefShader.hpp"
class GfLight : public GfObject
{
public:
	//vec3 color;
	//GLuint texture;
	//GLuint vao;
	//GLuint vbo;
	//GfShader * shader;
	GLuint shader_id;
	//bool is_vao_set = 0;
	//bool is_vbo_set = 0;
	//float ambient_intensity;
	//float diffuse_intensity;
	//float specular_intensity;
	void setup_light(GfShader* shader,glm::vec3 pos)
	{
		position = pos;
		this->shader_id= glGetUniformLocation(shader->getId(), "LightPosition_worldspace");

		//{
		//	glm::vec3 direction = glm::normalize(glm::vec3(0.0f, -1.0f, 1.0f));

		//	setUniform3f(shader_id, "directionalLight.direction", direction.x, direction.y, direction.z);
		//	setUniform3f(shader_id, "directionalLight.color", 1.0f, 1.0f, 1.0f);
		//	setUniform1f(shader_id, "directionalLight.ambientIntensity", float(directional_light_enabled)*ambient_intensity);
		//	setUniform1f(shader_id, "directionalLight.diffuseIntensity", float(directional_light_enabled)*diffuse_intensity);
		//	setUniform1f(shader_id, "directionalLight.specularIntensity", float(directional_light_enabled)*specular_intensity);
		//}

		//{
		//	setUniform3f(shader_id, "pointLight.position", position.x, position.y, position.z);
		//	setUniform3f(shader_id, "pointLight.color", 1.0f, 0.0f, 0.0f);
		//	setUniform1f(shader_id, "pointLight.ambientIntensity", float(point_light_enabled) * ambient_intensity);
		//	setUniform1f(shader_id, "pointLight.diffuseIntensity", float(point_light_enabled) * diffuse_intensity);
		//	setUniform1f(shader_id, "pointLight.specularIntensity", float(point_light_enabled) * specular_intensity);
		//}

		//{
		//	glm::vec3 direction = glm::normalize(glm::vec3(-0.5f, -1.0f, 0.0f));

		//	setUniform3f(shader_id, "spotLight.direction", direction.x, direction.y, direction.z);
		//	setUniform3f(shader_id, "spotLight.position", position.x, position.y, position.z);
		//	setUniform1f(shader_id, "spotLight.cutoff", glm::cos(glm::radians(15.0f)));
		//	setUniform3f(shader_id, "spotLight.color", 0.0f, 0.0f, 1.0f);
		//	setUniform1f(shader_id, "spotLight.ambientIntensity", float(spot_light_enabled)*ambient_intensity);
		//	setUniform1f(shader_id, "spotLight.diffuseIntensity", float(spot_light_enabled)*diffuse_intensity);
		//	setUniform1f(shader_id, "spotLight.specularIntensity", float(spot_light_enabled)*specular_intensity);
		//}
	}
	//void setVertices(std::vector<GLfloat> new_vertices)
	//{
	//	if (!is_vao_set)
	//		genVAO();
	//	glBindVertexArray(vao);


	//	if (!is_vbo_set)
	//		genVBO();
	//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//	glBufferData(GL_ARRAY_BUFFER, new_vertices.size() * sizeof(GLfloat), reinterpret_cast<void*>(new_vertices.data()), GL_STATIC_DRAW); //TO_DO set GL_DYNAMIC_DROW if obj rewriten
	//}
protected:
	//bool directional_light_enabled = 0;
	//bool point_light_enabled = 0;
	//bool spot_light_enabled = 0;
	/** Generate VAO array and store its handler in vao field
	*/
	//void genVAO()
	//{


	//	glGenVertexArrays(1, &vao);
	//	is_vao_set = true;
	//}
	///** Generate VBO array and store its handler in vbo field
	//*/
	//void genVBO()
	//{
	//	glGenBuffers(1, &vbo);
	//	is_vbo_set = true;
	//}
};

//class GfPointLight : public GfLight
//{
//protected:
//	bool point_light_enabled = 1;
//};
//
//class GfDirectionalLight : public GfLight
//{
//public:
//	vec3 direction;
//protected:
//	bool directional_light_enabled = 1;
//};
//
//class GfSpotLight : public GfLight
//{
//public:
//	vec3 direction;
//	float cutoff;
//protected:
//	bool spot_light_enabled = 1;
//};