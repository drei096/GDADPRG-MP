#pragma once
#include "ObjectPoolable.h"
class EnemyYellowCar : public ObjectPoolable
{
public:
	EnemyYellowCar(string name);
	void initialize();
	void onRelease();
	void onActivate();
	ObjectPoolable* clone();

private:
	int counter = 0;
};

