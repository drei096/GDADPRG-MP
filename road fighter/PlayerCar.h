#pragma once
#include "GameObject.h"
#include <iostream>

class PlayerCar : public GameObject
{
public:
	PlayerCar(string name);
	void initialize();

	int collisions = 0;

private:
	const float SPEED_MULTIPLIER = 300.0f; //temp, might change
	bool moveSecondGear = false;
	bool moveFirstGear = false;
	bool moveLeft = false;
	bool moveRight = false;
};

