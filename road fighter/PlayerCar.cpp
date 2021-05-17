#include "PlayerCar.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "PlayerInputController.h"
#include "PlayerMovement.h"
#include <SFML/Graphics.hpp>

PlayerCar::PlayerCar(string name) : GameObject(name)
{
}

void PlayerCar::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	Sprite* sprite = new Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("player"));
	Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->transformable.setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

	PlayerInputController* playerInput = new PlayerInputController("playerInput");
	this->attachComponent(playerInput);

	PlayerMovement* playerMovement = new PlayerMovement("playerMovement");
	this->attachComponent(playerMovement);

	Renderer* renderer = new Renderer("playerSprite");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);
	
}
