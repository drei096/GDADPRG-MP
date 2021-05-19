#pragma once
#include "ObjectComponent.h"

class EnemyCarClone : public ObjectComponent
{
public:
	EnemyCarClone(int numEnemies, string name);
	~EnemyCarClone();
	void perform();

private:
	const float SPAWN_INTERVAL = 0.01f;
	float ticks = 0.0f;
};

