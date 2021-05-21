#pragma once
#include "ObjectPoolable.h"
class FuelCar : public ObjectPoolable
{
public:
	FuelCar(string name);
	void initialize();
	void onRelease();
	void onActivate();
	ObjectPoolable* clone();

private:
	int counter = 0;
};

