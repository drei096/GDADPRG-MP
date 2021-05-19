#include "PlayerMovement.h"
#include "GameObject.h"
#include "PlayerInputController.h"
#include "Game.h"
#include <iostream>

PlayerMovement::PlayerMovement(string name) : ObjectComponent(name, Script)
{
}

PlayerMovement::~PlayerMovement()
{
	ObjectComponent::~ObjectComponent();
}

void PlayerMovement::perform()
{
	PlayerInputController* inputController = (PlayerInputController*)this->getOwner()->getComponentsOfType(componentType::Input)[0];
	Transformable* playerTransformable = this->getOwner()->getTransformable();

	if (playerTransformable == NULL || inputController == NULL) 
	{
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	Vector2f offset(0.0f, 0.0f);

	if (inputController->isSecondGear()) 
	{
		//cout << offset.x << " " << offset.y << endl;
		offset.y -= this->SPEED_MULTIPLIER;
		playerTransformable->move(offset * deltaTime.asSeconds());
	}
	else if (inputController->isFirstGear()) 
	{
		//this->resetSpeedMultiplier();

		//cout << offset.x << " " << offset.y << endl;
		offset.y += this->SPEED_MULTIPLIER;
		playerTransformable->move(offset * deltaTime.asSeconds());
	}

	else if (inputController->isRight()) 
	{
		//this->resetSpeedMultiplier();
		if (playerTransformable->getPosition().x >= ((Game::WINDOW_WIDTH / 2) + 65)) {
			playerTransformable->setPosition(playerTransformable->getPosition());
		}

		else {
			offset.x += this->SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}
	}
	else if (inputController->isLeft()) 
	{
		//this->resetSpeedMultiplier();
		if (playerTransformable->getPosition().x <= ((Game::WINDOW_WIDTH / 2) - 65)) {
			playerTransformable->setPosition(playerTransformable->getPosition());
		}

		else {
			offset.x -= this->SPEED_MULTIPLIER;
			playerTransformable->move(offset * deltaTime.asSeconds());
		}
	}
}

/*
void PlayerMovement::resetSpeedMultiplier()
{
	this->SPEED_MULTIPLIER = 300.0f;
}
*/