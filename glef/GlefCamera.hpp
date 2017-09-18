#pragma once
#include "common/commonIncludes.h"
#include "GlefObject.hpp"

class GfCamera : public GfObject
{
public:
	GfCamera();
	~GfCamera();
	/** Set camera position
	@param pos Camera position
	*/
	void setPosition(glm::vec3 pos)
	{
		position = pos;
		updateView();
	}
	/** Set camera direction
	@param direction Camera direction
	*/
	void setDirection(glm::vec3 direction)
	{
		look_at = direction;
		updateView();
	}
	/** Set cameras top direction
	@param direction_up Define direction of camera top, used to rotate camera upwords
	*/
	void setPositionUp(glm::vec3 direction_up)
	{
		up_at=direction_up;
		updateView();
	}
	/** Get Projection matrix
	@return Cameras projection martrix
	*/
	glm::mat4 getProjection()
	{
		return projection_matrix;
	}
	/** Get View matrix
	@return Cameras view martrix
	*/
	glm::mat4 getView()
	{
		return view_matrix;
	}
	/** Process with object to prepare it for rendering
	@param obj pointer to a processed object
	*/
	void preProcessObject(GfObject* obj)
	{
		obj->setMVP(projection_matrix*view_matrix*obj->modelMatrix());
	}
private:
	glm::vec3 look_at= glm::vec3(0, 0, 0);
	glm::vec3 up_at = glm::vec3(0, 1, 0);
	glm::mat4 view_matrix;
	glm::mat4 projection_matrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	/** Update camera matrix
	*/
	void updateView()
	{
		view_matrix=glm::lookAt(position, look_at, up_at);
	}
};

GfCamera::GfCamera()
{
}

GfCamera::~GfCamera()
{
}

class GfCameraFactory {
public:
	static GfCameraFactory& use()
	{
		static GfCameraFactory instance;
		return instance;
	}
	GfCameraFactory(GfCameraFactory const&) = delete;
	void operator=(GfCameraFactory const&) = delete;
	/** Create new camera
	@param pos Position of camera in absolute coordinates
	@param direction Point at which camera is looking
	@param up_direction Define direction of camera top, used to rotate camera upwords
	@return pointer on new camera
	*/
	GfCamera getCamera(glm::vec3 pos, glm::vec3 direction, glm::vec3 up_direction= glm::vec3(0, 1, 0))
	{
		GfCamera cam;
		cam.setDirection(direction);
		cam.setPosition(pos);
		cam.setPositionUp(up_direction);
		cam.setInitialized();
		return cam;
	}
private:
	GfCameraFactory() {};
};