#pragma once
#include "ObjectPoolable.h"
class OilSlick : public ObjectPoolable
{
public:
	OilSlick(string name);
	void initialize();
	void onRelease();
	void onActivate();
	ObjectPoolable* clone();

private:
	int counter = 0;
};


