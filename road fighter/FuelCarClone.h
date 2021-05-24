#pragma once
#include "ObjectComponent.h"
class FuelCarClone : public ObjectComponent
{
public:
	FuelCarClone(int numEnemies, string name);
	~FuelCarClone();
	void perform();

private:
	const float SPAWN_INTERVAL = 15.0f;
	float ticks = 0.0f;
};

