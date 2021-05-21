#pragma once
#include "ObjectComponent.h"
class EnemyYellowCarClone : public ObjectComponent
{
public:
	EnemyYellowCarClone(int numEnemies, string name);
	~EnemyYellowCarClone();
	void perform();

private:
	const float SPAWN_INTERVAL = 4.0f;
	float ticks = 0.0f;
};

