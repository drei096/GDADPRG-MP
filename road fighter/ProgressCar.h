#pragma once
#include "GameObject.h"
#include <iostream>

class ProgressCar : public GameObject
{
public:
	ProgressCar(string name);
	void initialize();

private:
	const float SPEED_MULTIPLIER = 300.0f; //temp, might change
	bool moveSecondGear = false;
	bool moveFirstGear = false;
	bool moveLeft = false;
	bool moveRight = false;
};

