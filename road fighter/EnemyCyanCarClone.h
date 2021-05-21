#pragma once
#include "ObjectComponent.h"
class EnemyCyanCarClone : public ObjectComponent
{
public:
	EnemyCyanCarClone(int numEnemies, string name);
	~EnemyCyanCarClone();
	void perform();

private:
	const float SPAWN_INTERVAL = 3.0f;
	float ticks = 0.0f;
};

