#pragma once
#include "ObjectComponent.h"
class EnemyTruckClone : public ObjectComponent
{
public:
	EnemyTruckClone(int numEnemies, string name);
	~EnemyTruckClone();
	void perform();

private:
	const float SPAWN_INTERVAL = 8.0f;
	float ticks = 0.0f;
};

