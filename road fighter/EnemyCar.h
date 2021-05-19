#pragma once
#include "ObjectPoolable.h"

class EnemyCar : public ObjectPoolable
{
public:
	EnemyCar(string name);
	void initialize();
	void onRelease();
	void onActivate();
	ObjectPoolable* clone();

private:
	int counter = 0;
};

