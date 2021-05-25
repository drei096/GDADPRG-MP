#pragma once
#include "ObjectComponent.h"
class PlayerMovement : public ObjectComponent
{
public:
	PlayerMovement(string name);
	~PlayerMovement();

	void perform();

private:
	const float SPEED_MULTIPLIER = 300.0f;
	float ticks = 0;
};

