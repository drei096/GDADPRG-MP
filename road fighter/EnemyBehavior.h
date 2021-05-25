#pragma once
#include "ObjectComponent.h"
class EnemyBehavior : public ObjectComponent
{
public:
	enum EnemyMovementType { Delay = 0, Forward = 1, Side = 2, SlowForward = 3 };
	enum Position { Left = 0, LeftMost = 1, Right = 2, RightMost = 3 };

	EnemyBehavior(string name, float _MULTIPLIER);
	void perform();
	void configure(float delay);
	void reset();

private:
	float SPEED_MULTIPLIER = 200.0f;
	EnemyMovementType movementType = Forward;
	Position position;
	float ticks = 0.0f;
	float delay = 0.0f;
	float prevX = 0.0f;
	int sideChoice = 0;
	float forwardDuration = 0.0f;
	bool isMoved = false;
	bool passed = false;
	bool isStart = false;
	bool goSide = false;
};

