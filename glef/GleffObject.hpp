#pragma once
//Standart libs
#include "common/commonIncludes.h"
#include "GlefModel.hpp"

class GfObject
{
public:
	/** Set mesh for object
	@param mesh_vertices array of mesh vertices
	*/
	void setMesh(std::vector<GLfloat> mesh_vertices)
	{
		mesh = std::make_unique<GfModel>();
		//mesh = std::unique_ptr<GfModel>(new GfModel());
		mesh->setVertices(mesh_vertices);
	}
	/** Set shader for object
	@param mesh_vertices pointer on a shader
	*/
	void setShader(std::shared_ptr<GfShader> shader)
	{
		this->shader = shader;
	}

	/** Called on every frame to drow object
	*/
	void useElement()
	{
		mesh->useElement(shader);
		for (auto i = 0; i < sub_objects.size(); i++)
			sub_objects[i].useElement();
	}
private:
	std::unique_ptr<GfModel> mesh;
	std::shared_ptr<GfShader> shader;
	std::vector<GfObject> sub_objects;
};
