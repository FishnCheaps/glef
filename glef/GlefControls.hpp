#pragma once
#include "common/commonIncludes.h"

class GfControls
{
public:
	GfControls();
	~GfControls();
	void setMoseAllowed(bool is_allowed)
	{
		is_mouse_allowed = is_allowed;
	}
	void setMovingAllowed(bool is_allowed)
	{
		is_mouse_allowed = is_allowed;
	}
	void setMouseSpeed(float speed)
	{
		mouse_speed = speed;
	}
	void setMovingSpeed(float speed)
	{
		moving_speed = speed;
	}
private:
	bool is_mouse_allowed = false;
	bool is_moving_allowed = false;
	float mouse_speed = 0;
	float moving_speed = 0;
};

GfControls::GfControls()
{
}

GfControls::~GfControls()
{
}