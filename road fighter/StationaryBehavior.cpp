#include "StationaryBehavior.h"
#include "GameObject.h"
#include <iostream>
#include "Game.h";
#include "ObjectPoolHolder.h"
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "GameObjectManager.h"
#include "UIText.h"
#include "LevelOverlay.h"

StationaryBehavior::StationaryBehavior(string name, float _MULTIPLIER) : ObjectComponent(name, Script)
{
	this->SPEED_MULTIPLIER = _MULTIPLIER;
	this->reset();
}

void StationaryBehavior::perform()
{
	PlayerCar* player = (PlayerCar*)GameObjectManager::getInstance()->findObjectByName("player");
	PlayerInputController* inputController = (PlayerInputController*)player->getComponentsOfType(componentType::Input)[0];
	UIText* textScore = (UIText*)GameObjectManager::getInstance()->findObjectByName("score_text");
	LevelOverlay* levelOverlay = (LevelOverlay*)GameObjectManager::getInstance()->findObjectByName("levelOverlay");

	//this->movementType = Side;


	this->ticks += this->deltaTime.asSeconds();
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	/*if (this->ticks > this->delay && this->movementType == Delay) {
		this->ticks = 0.0f;
		this->movementType = Forward;
		std::cout << "Ticks greater! " << this->getOwner()->getName() << "\n";
	}*/

	if (this->movementType == Forward) {

		if (inputController->isFirstGear() || inputController->isSecondGear())
		{
			transformable->move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER);
		}
		else
		{
			transformable->move(0, 0);
		}

		
		//check if position is out of bounds, we can delete/return to pool
		if (transformable->getPosition().y > Game::WINDOW_HEIGHT || transformable->getPosition().y < 0) {
			GameObjectManager::getInstance()->deleteObject((GameObject*)this->getOwner());

		}
		

	}


}

void StationaryBehavior::configure(float delay)
{
	this->delay += delay;
}

void StationaryBehavior::reset()
{
	//this->delay = (rand() % 3);
	this->movementType = Forward;
	//this->forwardDuration = (rand() % 3) + 1.0f;
	//this->forwardDuration = 1.0f;
	this->ticks = 0.0f;
}
