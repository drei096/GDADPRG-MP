#pragma once
#include "ObjectPoolable.h"
class EnemyCyanCar : public ObjectPoolable
{
public:
	EnemyCyanCar(string name);
	void initialize();
	void onRelease();
	void onActivate();
	ObjectPoolable* clone();

private:
	int counter = 0;
};

