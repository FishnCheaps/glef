#pragma once
//Standart libs
#include <iostream>
#include <vector>
#include <string>

//GL libs
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>

enum collors 
{ 
	Blue
};

class GfCollor {
public:
	float r;
	float g;
	float b;
	float a;
};

class GfCollorFactory {
public:
	static GfCollorFactory& use()
	{
		static GfCollorFactory instance;
		return instance;
	}
	GfCollorFactory(GfCollorFactory const&) = delete;
	void operator=(GfCollorFactory const&) = delete;
	/** Get GfCollor instance from RGBA values
	@param r Amount of red in RGBA (from 0 to 1)
	@param g Amount of green in RGBA (from 0 to 1)
	@param b Amount of blue in RGBA (from 0 to 1)
	@param a Alpha channel in RGBA (from 0 to 1)
	@returns Collor in GfCollor type
	*/
	GfCollor getCollor(float r, float g, float b, float a = 0) 
	{
		GfCollor new_collor;
		new_collor.r = r;
		new_collor.g = g;
		new_collor.b = b;
		new_collor.a = a;
		return new_collor;
	}
	/** Get GfCollor instance from collor name
	@param collor_name Collor name (from collors enum)
	@returns Collor in GfCollor type
	*/
	GfCollor getCollor(collors collor_name)
	{
		GfCollor new_collor;
		switch (collor_name)
		{
		case Blue:
			new_collor=getCollor(0.0f, 0.0f, 0.4f, 0.0f);
			break;
		default:
			break;
		}
		return new_collor;
	}
private:
	GfCollorFactory() {};
};