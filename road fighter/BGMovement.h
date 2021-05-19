#pragma once
#include "ObjectComponent.h"

class BGMovement : public ObjectComponent
{
public:
	BGMovement(string name, float _MAX);
	~BGMovement();
	void perform();


	float SPEED_MULTIPLIER = 1000.0f;
	float totalDistanceTravelled = 0.0f;
	float MAX_DISTANCE;
};

