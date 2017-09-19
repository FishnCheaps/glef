#pragma once

#include <math.h>
//Standart libs
#include "common/commonIncludes.h"
#include "GlefModel.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "GlefForce.hpp"


class GfObject
{
public:

	//refact
	glm::vec3 position = glm::vec3(0, 0, 0);
	float horizontal_angle = 0.0f;
	float vertical_angle = 0.0f;
	glm::mat4 model_matrix = glm::mat4(1.0f);
	glm::mat4 mvp = glm::mat4(1.0f);

	glm::mat4 rotation_matrix = glm::mat4(1.0f);
	glm::mat4 scaling_matrix = glm::mat4(1.0f);
	glm::mat4 translation_matrix = glm::mat4(1.0f);
	GfForce* force = nullptr;

	/** Get current initialization status
	return NOT_INITIALIZED if object is not initialized, or INITIALIZED otherwise
	*/
	glef_init_status staus()
	{
		return isInitialized;
	}
	/** Rotate object in XY plain
	@param degree rotation angle in degrees
	*/
	void rotateXYInst(float degree)
	{
		rotation_matrix = glm::rotate(rotation_matrix, degree, glm::vec3(0, 0, 1));
		xy_rot = fmod(xy_rot + degree, 360);
	}
	/** Rotate object in XZ plain
	@param degree rotation angle in degrees
	*/
	void rotateXZInst(float degree)
	{
		rotation_matrix = glm::rotate(rotation_matrix, degree, glm::vec3(0, 1, 0));
		xz_rot = fmod(xz_rot + degree, 360);
	}
	/** Rotate object in YZ plain
	@param degree rotation angle in degrees
	*/
	void rotateYZInst(float degree)
	{
		rotation_matrix = glm::rotate(rotation_matrix, degree, glm::vec3(1, 0, 0));
		yz_rot = fmod(yz_rot + degree, 360);
	}
	/** Scale object
	@param mult_x X axis multiplicator
	@param mult_x Y axis multiplicator
	@param mult_x Z axis multiplicator
	*/
	void scaleInst(float mult_x, float mult_y, float mult_z)
	{
		scaling_matrix = glm::scale(scaling_matrix, glm::vec3(mult_x, mult_y, mult_z));
	}
	/** Move object
	@param amound of units to move by X axis
	@param amound of units to move by Y axis
	@param amound of units to move by Z axis
	*/
	void moveInst(float mv_x, float mv_y, float mv_z)
	{
		translation_matrix = glm::translate(translation_matrix, glm::vec3(mv_x, mv_y, mv_z));
	}
	void moveInst(glm::vec3 new_position)
	{
		translation_matrix = glm::translate(translation_matrix, new_position-position);
	}
	/** Get model matrix
	@return Model matrix
	*/
	glm::mat4 modelMatrix()
	{
		return model_matrix;
	}
	/** Mark object as initialazed
	*/
	void setInitialized()
	{
		isInitialized = INITIALIZED;
	}
	/** Used to set starting parametres of object
	*/
	void init()
	{
		calcModelMatrix();
		postInit();
	}
	/** Do not touch or use this
	*/
	void proceed()
	{
		useElement();
		for (auto i = 0; i < sub_objects.size(); i++)
			sub_objects[i]->useElement();
	}
	/** Used to set mvp in camera
	@param mvp New mvp
	*/
	void setMVP(glm::mat4 mvp)
	{
		this->mvp = mvp;
	}
	/** Calculate model matrix
	*/
	void calcModelMatrix()
	{
		model_matrix = translation_matrix*rotation_matrix*scaling_matrix;
	}
protected:

	std::vector<GfObject*> sub_objects;
	glef_init_status isInitialized = NOT_INITIALIZED;
	/** Called on every frame to drow object
	*/
	virtual void useElement()
	{
	}
	virtual void postInit()
	{
	}
	//---Positioning and rotating
	float xy_rot = 0;
	float yz_rot = 0;
	float xz_rot = 0;

};
