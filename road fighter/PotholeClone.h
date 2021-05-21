#pragma once
#include "ObjectComponent.h"
class PotholeClone : public ObjectComponent
{
public:
	PotholeClone(int numEnemies, string name);
	~PotholeClone();
	void perform();

private:
	const float SPAWN_INTERVAL = 5.0f;
	float ticks = 0.0f;
};

