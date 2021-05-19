#include "EnemyCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "EnemyBehavior.h"
#include <iostream>
#include "Renderer.h"
#include "Collider.h"
#include "PhysicsManager.h"

EnemyCar::EnemyCar(string name) : ObjectPoolable(name)
{

}

void EnemyCar::initialize()
{
	//assign texture
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("enemyCar"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	sprite->setScale(0.7, 0.7);

	this->setPosition(Game::WINDOW_WIDTH / 2, -30);
	//randomize
	this->getTransformable()->move(rand() % 300 - rand() % 300, 0);
	//this->getTransformable()->setRotation(180); //must face towards player


	Renderer* renderer = new Renderer("EnemySprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	
	EnemyBehavior* behavior = new EnemyBehavior("EnemyBehavior");
	this->attachComponent(behavior);
	behavior->configure(1.0f);

	
	Collider* collide = new Collider("EnemyCollide", sprite, Collider::ObjectType::EnemyCar);
	this->attachComponent(collide);
	PhysicsManager::getInstance()->trackObject(collide);
	
}

void EnemyCar::onRelease()
{
	EnemyBehavior* behavior = (EnemyBehavior*)this->findComponentByName("EnemyBehavior");
	behavior->reset();
	this->setPosition(Game::WINDOW_WIDTH / 2, -30);
	//randomize
	this->getTransformable()->move(rand() % 65 - rand() % 65, 0);
}

void EnemyCar::onActivate()
{
	//reset state
	EnemyBehavior* behavior = (EnemyBehavior*)this->findComponentByName("EnemyBehavior");
	behavior->reset();
	this->setPosition(Game::WINDOW_WIDTH / 2, -30);
	//randomize
	this->getTransformable()->move(rand() % 65 - rand() % 65, 0);
}

ObjectPoolable* EnemyCar::clone()
{
	ObjectPoolable* copyObj = new EnemyCar(this->name);
	return copyObj;
}