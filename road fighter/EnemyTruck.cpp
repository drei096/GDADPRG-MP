#include "EnemyTruck.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior.h"
#include <iostream>
#include "Renderer.h"
#include "Collider.h"
#include "PhysicsManager.h"


EnemyTruck::EnemyTruck(string name) : ObjectPoolable(name)
{
}

void EnemyTruck::initialize()
{
	srand(time(NULL));
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("enemyCivCars"));

	sprite->setTextureRect(sf::IntRect(0, 0, 44, 84)); //truck car from spritesheet
	sprite->setScale(0.5, 0.5);

	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(44 / 2, 84 / 2);
	sprite->setScale(0.5, 0.5);

	this->setPosition((rand()%(Game::WINDOW_WIDTH / 2) - 25), Game::WINDOW_HEIGHT);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1), 0);
	//this->getTransformable()->setRotation(180); //must face towards player


	Renderer* renderer = new Renderer("EnemyTruckSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	EnemyBehavior* behavior = new EnemyBehavior("EnemyTruckBehavior", 200.0f);
	this->attachComponent(behavior);
	behavior->configure(1.0f);


	Collider* collide = new Collider("EnemyCollide", sprite, Collider::ObjectType::EnemyCar);
	this->attachComponent(collide);
	PhysicsManager::getInstance()->trackObject(collide);
}

void EnemyTruck::onRelease()
{
	EnemyBehavior* behavior = (EnemyBehavior*)this->findComponentByName("EnemyTruckBehavior");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1), 0);
}

void EnemyTruck::onActivate()
{
	EnemyBehavior* behavior = (EnemyBehavior*)this->findComponentByName("EnemyTruckBehavior");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1), 0);
}

ObjectPoolable* EnemyTruck::clone()
{
	ObjectPoolable* copyObj = new EnemyTruck(this->name);
	return copyObj;
}
