#pragma once
#include "ObjectComponent.h"

class BGMovement : public ObjectComponent
{
public:
	BGMovement(string name, float _MAX, int _level);
	~BGMovement();
	void perform();
	float laneCheck();

	float SPEED_MULTIPLIER = 0.0f;
	float totalDistanceTravelled = 0.0f;
	float MAX_DISTANCE;
	bool leftMost = false;
	bool left = false;
	bool right = false;
	bool rightMost = false;
	int level;
};

