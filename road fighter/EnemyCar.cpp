#include "EnemyCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior.h"
#include <iostream>
#include "Renderer.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "NormalEnemyBehavior.h"

EnemyCar::EnemyCar(string name) : ObjectPoolable(name)
{
	
}

void EnemyCar::initialize()
{
	srand(time(NULL));
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("enemyCivCars"));

	sprite->setTextureRect(sf::IntRect(245, 0, 300, 340)); //blue car from spritesheet
	sprite->setScale(0.5, 0.5);

	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(300 / 2, 340 / 2);
	sprite->setScale(0.12, 0.12);

	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, Game::WINDOW_HEIGHT * 5);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1) , 0);
	//this->getTransformable()->setRotation(180); //must face towards player


	Renderer* renderer = new Renderer("EnemySprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	
	NormalEnemyBehavior* behavior = new NormalEnemyBehavior("EnemyBehavior", 400.0f);
	this->attachComponent(behavior);
	//behavior->configure(1.0f);

	
	Collider* collide = new Collider("EnemyCollide", sprite, Collider::ObjectType::EnemyCar);
	this->attachComponent(collide);
	PhysicsManager::getInstance()->trackObject(collide);
	
}

void EnemyCar::onRelease()
{
	NormalEnemyBehavior* behavior = (NormalEnemyBehavior*)this->findComponentByName("EnemyBehavior");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1), 0);
	this->setEnabled(false);
}

void EnemyCar::onActivate()
{
	//reset state
	NormalEnemyBehavior* behavior = (NormalEnemyBehavior*)this->findComponentByName("EnemyBehavior");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1), 0);
	this->setEnabled(false);
}

ObjectPoolable* EnemyCar::clone()
{
	ObjectPoolable* copyObj = new EnemyCar(this->name);
	return copyObj;
}