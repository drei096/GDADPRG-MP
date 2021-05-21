#include "EnemyBehavior.h"
#include "GameObject.h"
#include <iostream>
#include "Game.h";
#include "ObjectPoolHolder.h"

EnemyBehavior::EnemyBehavior(string name, float _MULTIPLIER) : ObjectComponent(name, Script)
{
	this->SPEED_MULTIPLIER = _MULTIPLIER;
	this->reset();
}

void EnemyBehavior::perform()
{
	
	//this->movementType = Side;
	

	this->ticks += this->deltaTime.asSeconds();
	sf::Transformable* transformable = this->getOwner()->getTransformable();

	/*if (this->ticks > this->delay && this->movementType == Delay) {
		this->ticks = 0.0f;
		this->movementType = Forward;
		std::cout << "Ticks greater! " << this->getOwner()->getName() << "\n";
	}*/

	if (this->movementType == Forward) {

		transformable->move(0, this->deltaTime.asSeconds() * SPEED_MULTIPLIER);
		
		//check if position is out of bounds, we can delete/return to pool
		if (transformable->getPosition().y > Game::WINDOW_HEIGHT) {
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
			ObjectPoolHolder::getInstance()->getPool(ObjectPoolHolder::ENEMY_CYAN_CAR_POOL_TAG)->releasePoolable((ObjectPoolable*)this->getOwner());
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
