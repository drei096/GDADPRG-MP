#pragma once
#include "ObjectComponent.h"
class EnemyBehavior : public ObjectComponent
{
public:
	enum EnemyMovementType { Delay = 0, Forward = 1, SlowForward = 2, Side = 3 };

	EnemyBehavior(string name, float _MULTIPLIER);
	void perform();
	void configure(float delay);
	void reset();

private:
	float SPEED_MULTIPLIER = 200.0f;
	EnemyMovementType movementType = Forward;
	float ticks = 0.0f;
	float delay = 0.0f;
	float forwardDuration = 0.0f;
};

