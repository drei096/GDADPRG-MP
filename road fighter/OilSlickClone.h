#pragma once
#include "ObjectComponent.h"
class OilSlickClone : public ObjectComponent
{
public:
	OilSlickClone(int numEnemies, string name);
	~OilSlickClone();
	void perform();

private:
	const float SPAWN_INTERVAL = 0.05f;
	float ticks = 0.0f;
};

