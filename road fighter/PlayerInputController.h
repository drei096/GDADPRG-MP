#pragma once
#include "InputController.h"
class PlayerInputController : public InputController
{
public:
	PlayerInputController(string name);
	~PlayerInputController();

	void perform();
	bool isSecondGear();
	bool isFirstGear();
	bool isLeft();
	bool isRight();
	bool Honk();

private:
	const float SPEED_MULTIPLIER = 300.0f;
	bool moveSecondGear = false;
	bool moveFirstGear = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool isHonk = false;
};

