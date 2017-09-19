#pragma once
#include "common/commonIncludes.h"

class GfControls
{
public:
	GfControls();
	~GfControls();
	void setRotatingAllowed(bool is_allowed)
	{
		is_rotating_allowed = is_allowed;
	}
	void setMovingAllowed(bool is_allowed)
	{
		is_moving_allowed = is_allowed;
	}
	int key_right = GLFW_KEY_RIGHT;
	int key_left = GLFW_KEY_LEFT;
	int key_up = GLFW_KEY_UP;
	int key_down = GLFW_KEY_DOWN;
	int key_size_up = GLFW_KEY_0;
	int key_size_down = GLFW_KEY_1;
	bool is_rotating_allowed = false;
	bool is_moving_allowed = false;
	bool is_sizing_allowed = false;
	float speed = 3.0f;
	float mouseSpeed = 0.005f;
	float sizingSpeed = 1.0f;
private:
};

GfControls::GfControls()
{
}

GfControls::~GfControls()
{
}