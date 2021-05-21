#pragma once
#include "ObjectPoolable.h"
class Pothole : public ObjectPoolable
{
public:
	Pothole(string name);
	void initialize();
	void onRelease();
	void onActivate();
	ObjectPoolable* clone();

private:
	int counter = 0;
};

