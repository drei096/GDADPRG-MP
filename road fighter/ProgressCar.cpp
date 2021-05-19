#include "ProgressCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "CarProgressMovement.h"
#include <SFML/Graphics.hpp>

ProgressCar::ProgressCar(string name) : GameObject(name)
{
}

void ProgressCar::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	Sprite* sprite = new Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("player"));
	Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	//sprite->setScale(0.5, 0.5);

	CarProgressMovement* carProgressMovement = new CarProgressMovement("carProgress");
	this->attachComponent(carProgressMovement);

	Renderer* renderer = new Renderer("progressSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

}
