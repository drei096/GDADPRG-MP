#include "EnemyBehavior.h"
#include "GameObject.h"
#include <iostream>
#include "Game.h";
#include "ObjectPoolHolder.h"
#include "PlayerCar.h"
#include "PlayerInputController.h"
#include "GameObjectManager.h"
#include "UIText.h"
#include "LevelOverlay.h"

EnemyBehavior::EnemyBehavior(string name, float _MULTIPLIER) : ObjectComponent(name, Script)
{
	this->SPEED_MULTIPLIER = _MULTIPLIER;
	this->reset();
}

void EnemyBehavior::perform()
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
			transformable->move(0, this->deltaTime.asSeconds() * -SPEED_MULTIPLIER * 0.8);
		}


		//check if position is out of bounds, we can delete/return to pool
		if (transformable->getPosition().y > Game::WINDOW_HEIGHT || transformable->getPosition().y < 0) {
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CYAN_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_FUEL_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_TRUCK_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_YELLOW_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::POTHOLE_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
		}

		
		if ((int)this->ticks % 5 == 0 && (int)this->ticks != 0)
		{
			//cout << "true" << endl;
			this->movementType = Side;
		}
		
	}

	if (this->movementType == Side)
	{
		if (transformable->getPosition().x < 0)
		{
			transformable->move(this->deltaTime.asSeconds() * SPEED_MULTIPLIER, 0);
		}

		if (transformable->getPosition().x >= 60)
		{
			this->movementType = Forward;
		}
	}

	//TEMPORARY: just here to check if setEnabled flags work
	/*if (this->ticks > this->delay) {
		this->getOwner()->setEnabled(false);
	}*/

}

void EnemyBehavior::configure(float delay)
{
	this->delay += delay;
}

void EnemyBehavior::reset()
{
	//this->delay = (rand() % 3);
	this->movementType = Forward;
	//this->forwardDuration = (rand() % 3) + 1.0f;
	//this->forwardDuration = 1.0f;
	this->ticks = 0.0f;
}
