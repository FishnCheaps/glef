#pragma once
#include "common/commonIncludes.h"
#include "GlefModel.hpp"
#include "GlefCamera.hpp"
#include "GlefControls.hpp"
#include "GlefShader.hpp"
#include "GlefTexture.hpp"
#include "GlefForce.hpp"
#include "GlefLight.hpp"

class GfRenderEngine
{
public:
	GfRenderEngine();
	~GfRenderEngine();


	void RenderModelWithMovableCameraForLight(GfModel* model, GfTexture texture, GfCameraActive * camera, GfWindow * window, GfControls * controls, GfShader * shader, GfLight * light)
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(shader->getId());
		//computeCameraMatricesFromInputs(camera, window, controls);
		// Compute the MVP matrix from keyboard and mouse input
		computeCameraMatricesFromInputs(camera, window, controls);
		glm::mat4 ProjectionMatrix = camera->projection_matrix;
		glm::mat4 ViewMatrix = camera->view_matrix;
		glm::mat4 ModelMatrix = model->model_matrix;                    //!!!!!!
		model->mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(model->matrix_id, 1, GL_FALSE, &model->mvp[0][0]);
		glUniformMatrix4fv(model->ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(camera->ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		glm::vec3 lightPos = light->position;
		glUniform3f(light->shader_id, lightPos.x, lightPos.y, lightPos.z);


		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(texture.texture_id, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, texture.uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, model->normal);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, model->vertices.size()); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		// Swap buffers
		//glfwSwapBuffers(window->window_ptr);
		//glfwPollEvents();

	}

	void RenderModelWithMovableCameraForEveryObjectTextured(GfModel* model,GfTexture texture, GfCameraActive * camera, GfWindow * window, GfControls * controls, GfShader * shader)
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(shader->getId());
		//computeCameraMatricesFromInputs(camera, window, controls);
		// Compute the MVP matrix from keyboard and mouse input
		computeCameraMatricesFromInputs(camera,window,controls);
		glm::mat4 ProjectionMatrix = camera->projection_matrix;
		glm::mat4 ViewMatrix =camera->view_matrix;
		glm::mat4 ModelMatrix = model->model_matrix;                    //!!!!!!
		model->mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(model->matrix_id, 1, GL_FALSE, &model->mvp[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture.texture);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(texture.texture_id, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, texture.uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, model->vertices.size()); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		//glfwSwapBuffers(window->window_ptr);
		//glfwPollEvents();

	}
	void RenderModelWithMovableCameraForEveryObjectColored(GfModel* model, GfCameraActive * camera, GfWindow * window, GfControls * controls, GfShader * shader)
	{
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(shader->getId());
		//computeCameraMatricesFromInputs(camera, window, controls);
		// Compute the MVP matrix from keyboard and mouse input
		computeCameraMatricesFromInputs(camera, window, controls);
		glm::mat4 ProjectionMatrix = camera->projection_matrix;
		glm::mat4 ViewMatrix = camera->view_matrix;
		glm::mat4 ModelMatrix = model->model_matrix;                    //!!!!!!
		model->mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(model->matrix_id, 1, GL_FALSE, &model->mvp[0][0]);
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, model->color);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, model->vertices.size()); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

	}
	void computeCameraMatricesFromInputs(GfCameraActive * camera, GfWindow * window, GfControls * controls) {

		// glfwGetTime is called only once, the first time this function is called
		static double lastTime = glfwGetTime();

		// Compute time difference between current and last frame
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);

		// Get mouse position
		double xpos, ypos;
		glfwGetCursorPos(window->window_ptr, &xpos, &ypos);

		// Reset mouse position for next frame
		glfwSetCursorPos(window->window_ptr, window->width / 2, window->height / 2);

		// Compute new orientation
		camera->horizontal_angle += controls->mouseSpeed* float(window->width / 2 - xpos);
		camera->vertical_angle += controls->mouseSpeed* float(window->height / 2 - ypos);

		// Direction : Spherical coordinates to Cartesian coordinates conversion
		glm::vec3 direction(
			cos(camera->vertical_angle) * sin(camera->horizontal_angle),
			sin(camera->vertical_angle),
			cos(camera->vertical_angle) * cos(camera->horizontal_angle)
		);

		// Right vector
		glm::vec3 right = glm::vec3(
			sin(camera->horizontal_angle - 3.14f / 2.0f),
			0,
			cos(camera->horizontal_angle - 3.14f / 2.0f)
		);

		// Up vector
		glm::vec3 up = glm::cross(right, direction);

		// Move forward
		if (glfwGetKey(window->window_ptr, controls->key_up) == GLFW_PRESS) {
			camera->position += direction * deltaTime * controls->speed;
		}
		// Move backward
		if (glfwGetKey(window->window_ptr, controls->key_down) == GLFW_PRESS) {
			camera->position -= direction * deltaTime * controls->speed;
		}
		// Strafe right
		if (glfwGetKey(window->window_ptr, controls->key_right) == GLFW_PRESS) {
			camera->position += right * deltaTime * controls->speed;
		}
		// Strafe left
		if (glfwGetKey(window->window_ptr, controls->key_left) == GLFW_PRESS) {
			camera->position -= right * deltaTime * controls->speed;
		}

		float FoV = camera->initial_fov;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

										// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		camera->projection_matrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
		// Camera matrix
		camera->view_matrix = glm::lookAt(
			camera->position,           // Camera is here
			camera->position + direction, // and looks here : at the same position, plus "direction"
			up                  // Head is up (set to 0,-1,0 to look upside-down)
		);

		// For the next frame, the "last time" will be "now"
		lastTime = currentTime;
	}
	void computeModelMatricesFromInputs(GfObject * object, GfWindow * window, GfControls * controls) {

		// glfwGetTime is called only once, the first time this function is called
		static double lastTime = glfwGetTime();

		// Compute time difference between current and last frame
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);

		// Get mouse position
		double xpos, ypos;
		glfwGetCursorPos(window->window_ptr, &xpos, &ypos);

		// Reset mouse position for next frame
		glfwSetCursorPos(window->window_ptr, window->width / 2, window->height / 2);

		// Compute new orientation
		object->horizontal_angle = controls->mouseSpeed* float(window->width / 2 - xpos);
		object->vertical_angle = controls->mouseSpeed* float(window->height / 2 - ypos);

		// Direction : Spherical coordinates to Cartesian coordinates conversion
		glm::vec3 direction(
			cos(object->vertical_angle) * sin(object->horizontal_angle),
			sin(object->vertical_angle),
			cos(object->vertical_angle) * cos(object->horizontal_angle)
		);

		// Right vector
		glm::vec3 right = glm::vec3(
			sin(object->horizontal_angle - 3.14f / 2.0f),
			0,
			cos(object->horizontal_angle - 3.14f / 2.0f)
		);

		// Up vector
		glm::vec3 up = glm::cross(right, direction);

		object->rotation_matrix = glm::mat3(right, up, direction);

		// Move forward
		glm::vec3 old_pos = object->position;
		if (glfwGetKey(window->window_ptr, controls->key_up) == GLFW_PRESS) {
			old_pos += direction * deltaTime * controls->speed;
		}
		// Move backward
		if (glfwGetKey(window->window_ptr, controls->key_down) == GLFW_PRESS) {
			old_pos -= direction * deltaTime * controls->speed;
		}
		// Strafe right
		if (glfwGetKey(window->window_ptr, controls->key_right) == GLFW_PRESS) {
			old_pos += right * deltaTime * controls->speed;
		}
		// Strafe left
		if (glfwGetKey(window->window_ptr, controls->key_left) == GLFW_PRESS) {
			old_pos -= right * deltaTime * controls->speed;
		}
		object->moveInst(old_pos);
		object->position = old_pos;
		object->calcModelMatrix();
		//float FoV = camera->initial_fov;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		//camera->projection_matrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
		// Camera matrix
		//camera->view_matrix = glm::lookAt(
		//	camera->position,           // Camera is here
		//	camera->position + direction, // and looks here : at the same position, plus "direction"
		//	up                  // Head is up (set to 0,-1,0 to look upside-down)
		//);
		// For the next frame, the "last time" will be "now"
		lastTime = currentTime;
	}
	void computeModelMatricesFromForce(GfObject * object, GfWindow * window, GfForce * force) {

		// glfwGetTime is called only once, the first time this function is called
		static double lastTime = glfwGetTime();

		// Compute time difference between current and last frame
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);

		object->moveInst(force->force_x*deltaTime, force->force_y*deltaTime, force->force_z*deltaTime);
		object->rotateXYInst(force->rot_z*deltaTime);
		object->rotateYZInst(force->rot_x*deltaTime);
		object->rotateXZInst(force->rot_y*deltaTime);
		object->calcModelMatrix();
		//float FoV = camera->initial_fov;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		//camera->projection_matrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
		// Camera matrix
		//camera->view_matrix = glm::lookAt(
		//	camera->position,           // Camera is here
		//	camera->position + direction, // and looks here : at the same position, plus "direction"
		//	up                  // Head is up (set to 0,-1,0 to look upside-down)
		//);
		// For the next frame, the "last time" will be "now"
		lastTime = currentTime;
	}
private:
	
};

GfRenderEngine::GfRenderEngine()
{
}

GfRenderEngine::~GfRenderEngine()
{
}