#include "EnemyYellowCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior.h"
#include <iostream>
#include "Renderer.h"
#include "Collider.h"
#include "PhysicsManager.h"
#include "BGMovement.h"
#include "GameObjectManager.h"

EnemyYellowCar::EnemyYellowCar(string name) : ObjectPoolable(name)
{
}

void EnemyYellowCar::initialize()
{
	srand(time(NULL));
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("enemyCivCars"));

	sprite->setTextureRect(sf::IntRect(475, 0, 300, 340)); //yellow car from spritesheet
	sprite->setScale(0.5, 0.5);

	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(300 / 2, 340 / 2);
	sprite->setScale(0.12, 0.12);

	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -Game::WINDOW_HEIGHT * 50);
	//randomize position
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1), 0);


	Renderer* renderer = new Renderer("EnemyYellowSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	EnemyBehavior* behavior = new EnemyBehavior("EnemyYellowBehavior", 400.0f);
	this->attachComponent(behavior);

	Collider* collide = new Collider("EnemyCollide", sprite, Collider::ObjectType::EnemyCar);
	this->attachComponent(collide);
	PhysicsManager::getInstance()->trackObject(collide);
}

void EnemyYellowCar::onRelease()
{
	EnemyBehavior* behavior = (EnemyBehavior*)this->findComponentByName("EnemyYellowBehavior");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	int sign = rand() % 2;
	this->getTransformable()->move((65 / ((rand() % 2) + 1)) * ((sign > 0) ? -1 : 1), 0);
}

void EnemyYellowCar::onActivate()
{
	EnemyBehavior* behavior = (EnemyBehavior*)this->findComponentByName("EnemyYellowBehavior");
	BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");
	behavior->reset();
	this->setPosition((Game::WINDOW_WIDTH / 2) - 25, -30);
	//randomize
	float posX = bgMove->laneCheck();
	this->getTransformable()->move(posX, 0);
}

ObjectPoolable* EnemyYellowCar::clone()
{
	ObjectPoolable* copyObj = new EnemyYellowCar(this->name);
	return copyObj;
}
