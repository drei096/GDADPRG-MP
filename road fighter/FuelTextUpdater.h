#pragma once
#include "ObjectComponent.h"
class FuelTextUpdater : public ObjectComponent
{
public:
	FuelTextUpdater(string name);
	~FuelTextUpdater();

	void perform();
	float ticks = 0;
};
