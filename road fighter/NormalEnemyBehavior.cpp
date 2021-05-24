#include "NormalEnemyBehavior.h"
#include "GameObject.h"
#include <iostream>
#include "Game.h";
#include "ObjectPoolHolder.h"
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "GameObjectManager.h"
#include "UIText.h"
#include "LevelOverlay.h"

NormalEnemyBehavior::NormalEnemyBehavior(string name, float _MULTIPLIER) : ObjectComponent(name, Script)
{
	this->SPEED_MULTIPLIER = _MULTIPLIER;
	this->reset();
}

void NormalEnemyBehavior::perform()
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

		if (inputController->isSecondGear())
		{
			if (transformable->getPosition().y > 0) {
				this->isStart = true;
			}
			transformable->move(0, this->deltaTime.asSeconds()* SPEED_MULTIPLIER);
			if (transformable->getPosition().y > player->getTransformable()->getPosition().y && !this->passed) {
				if (this->owner->getName() != "enemyFuel") {
					player->passedCar++;
				}
				this->passed = true;
			}
		}
		else
		{
			transformable->move(0, this->deltaTime.asSeconds() * -SPEED_MULTIPLIER * 0.8);
			if (transformable->getPosition().y < player->getTransformable()->getPosition().y && this->passed) {
				player->passedCar--;
				this->passed = false;
			}
		}

		
		//check if position is out of bounds, we can delete/return to pool
		if ((transformable->getPosition().y > Game::WINDOW_HEIGHT || transformable->getPosition().y < 0) && this->isStart) {
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			cout << "paalam" << endl;
			this->isStart = false;
		}
		

	}


}

void NormalEnemyBehavior::configure(float delay)
{
	this->delay += delay;
}

void NormalEnemyBehavior::reset()
{
	//this->delay = (rand() % 3);
	this->movementType = Forward;
	//this->forwardDuration = (rand() % 3) + 1.0f;
	//this->forwardDuration = 1.0f;
	this->ticks = 0.0f;
	this->passed = false;
}

