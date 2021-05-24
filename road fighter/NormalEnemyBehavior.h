#pragma once
#include "ObjectComponent.h"
class NormalEnemyBehavior : public ObjectComponent
{
public:
	enum EnemyMovementType { Delay = 0, Forward = 1, Side = 2, SlowForward = 3 };

	NormalEnemyBehavior(string name, float _MULTIPLIER);
	void perform();
	void configure(float delay);
	void reset();

private:
	float SPEED_MULTIPLIER = 200.0f;
	EnemyMovementType movementType = Forward;
	float ticks = 0.0f;
	float delay = 0.0f;
	float forwardDuration = 0.0f;
	bool isStart = false;
	bool passed = false;
};

