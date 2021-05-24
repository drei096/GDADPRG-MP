#include "PlayerCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"
#include <SFML/Graphics.hpp>
#include "PhysicsManager.h"
#include "ShortTimeCollisions.h"
#include "Collider.h"

PlayerCar::PlayerCar(string name, int enemyCount) : GameObject(name)
{
	this->totalEnemies = enemyCount;
}

void PlayerCar::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	Sprite* sprite = new Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("player"));
	Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	sprite->setScale(0.6, 0.6);
	this->transformable.setPosition((Game::WINDOW_WIDTH / 2) - 25, (Game::WINDOW_HEIGHT / 2) + 100);

	PlayerInputController* playerInput = new PlayerInputController("playerInput");
	this->attachComponent(playerInput);

	PlayerMovement* playerMovement = new PlayerMovement("playerMovement");
	this->attachComponent(playerMovement);

	Collider* collide = new Collider("PlayerCollide", sprite, Collider::ObjectType::Player);
	this->attachComponent(collide);
	PhysicsManager::getInstance()->trackObject(collide);

	ShortTimeCollisions* shortCol = new ShortTimeCollisions("shortTimeCollisions");
	this->attachComponent(shortCol);

	Renderer* renderer = new Renderer("playerSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);
	
}
