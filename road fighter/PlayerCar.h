#pragma once
#include "GameObject.h"
#include <iostream>

class PlayerCar : public GameObject
{
public:
	PlayerCar(string name, int enemyCount);
	void initialize();

	int collisions = 0;
	int speedCollision = 0;
	int passedCar = 0;
	int totalEnemies = 0;
	bool isCollidedFuel = false;
	bool hasPassedACar = false;

private:
	const float SPEED_MULTIPLIER = 300.0f; //temp, might change
	bool moveSecondGear = false;
	bool moveFirstGear = false;
	bool moveLeft = false;
	bool moveRight = false;
};

