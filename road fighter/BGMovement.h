#pragma once
#include "ObjectComponent.h"

class BGMovement : public ObjectComponent
{
public:
	BGMovement(string name);
	~BGMovement();
	void perform();

private:
	const float SPEED_MULTIPLIER = 1000.0f;
};

