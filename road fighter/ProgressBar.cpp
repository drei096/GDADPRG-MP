#include "ProgressBar.h"
#include "TextureManager.h"
#include "Game.h"
#include "UIButton.h"
#include "UIText.h"
#include "GameObjectManager.h"
#include "Renderer.h"
#include "ProgressCar.h"
#include "CarProgressMovement.h"

ProgressBar::ProgressBar(string name) :GameObject(name), ButtonListener()
{

}

ProgressBar::~ProgressBar()
{
	GameObject::~GameObject();
}

void ProgressBar::initialize()
{
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("popUpYellow"));
	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	//sprite->setColor(sf::Color::Cyan);
	this->setPosition(50, Game::WINDOW_HEIGHT / 2);
	this->getTransformable()->setScale(1.0f, 0.25f);
	this->getTransformable()->setRotation(90);

	ProgressCar* progressCar = new ProgressCar("progressCar");
	this->attachChild(progressCar);
	progressCar->getTransformable()->setRotation(-90);
	progressCar->getTransformable()->setScale(2.25f, 0.5f);
	progressCar->getTransformable()->setPosition(250,0);

	Renderer* renderer = new Renderer("ProgressRender");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);


}

void ProgressBar::onButtonClick(UIButton* button)
{

}

void ProgressBar::onButtonReleased(UIButton* button)
{

}
