#pragma once
#include "ObjectPoolable.h"
class EnemyTruck : public ObjectPoolable
{
public:
	EnemyTruck(string name);
	void initialize();
	void onRelease();
	void onActivate();
	ObjectPoolable* clone();

private:
	int counter = 0;
};

