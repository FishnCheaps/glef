#pragma once
//Standart libs
#include <iostream>
#include <vector>
#include <string>

//GL libs
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>

//Glef libs
#include "GlefCollor.hpp"

class GfWindow 
{
public:
	GfWindow() {};
	GfWindow(GLFWwindow*) {};
	GLFWwindow* window_ptr;
	/** Set window background collor
	@param collor Collor to set
	*/
	void setBackgroundCollor(GfCollor collor)
	{
		background_collor = collor;
		glClearColor(collor.r, collor.g, collor.b, collor.a);
	}
	/** Get window current background collor
	@returns Window current background collor
	*/
	GfCollor getBackgroundCollor()
	{
		return background_collor;
	}
private:
	GfCollor background_collor;
};