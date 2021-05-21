#pragma once
#include "ObjectComponent.h"
class FuelTextUpdater : public ObjectComponent
{
public:
	FuelTextUpdater(string name);
	~FuelTextUpdater();

	void perform();
	float ticks = 0;
	float lowFuel = 0;
	float currfuel = 100;
};

