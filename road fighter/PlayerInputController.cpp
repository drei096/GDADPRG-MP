#include "PlayerInputController.h"

PlayerInputController::PlayerInputController(string name) : InputController(name)
{
}

PlayerInputController::~PlayerInputController()
{
	InputController::~InputController();
}

void PlayerInputController::perform()
{
	bool keyDown = false;
	if (event.type == Event::KeyPressed)
	{
		keyDown = true;
	}
	
	else if (event.type == Event::KeyReleased)
	{
		keyDown = false;
	}
	
	switch (event.key.code) 
	{
	case Keyboard::W:
		this->moveSecondGear = keyDown;
		break;
	case Keyboard::A:
		this->moveLeft = keyDown;
		break;
	case Keyboard::S:
		this->moveFirstGear = keyDown;
		break;
	case Keyboard::D:
		this->moveRight = keyDown;
		break;
	case Keyboard::Space:
		this->isHonk = keyDown;
		break;
	}
}

bool PlayerInputController::isSecondGear()
{
	return this->moveSecondGear;
}

bool PlayerInputController::isFirstGear()
{
	return this->moveFirstGear;
}

bool PlayerInputController::isLeft()
{
	return this->moveLeft;
}

bool PlayerInputController::isRight()
{
	return this->moveRight;
}

bool PlayerInputController::Honk()
{
	return this->isHonk;
}
