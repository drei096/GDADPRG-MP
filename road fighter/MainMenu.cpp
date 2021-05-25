#include "MainMenu.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "UIButton.h"
#include "UIText.h"
#include "GameObjectManager.h"
#include "ApplicationManager.h"
#include "SceneManager.h"
#include "SFXManager.h"
#include <iostream>

MainMenu::MainMenu(string name) : GameObject(name), ButtonListener()
{
}

MainMenu::~MainMenu()
{
	GameObject::~GameObject();
}

void MainMenu::initialize()
{
	SFXManager::getInstance()->play("menuBGM");
	SFXManager::getInstance()->setVolume("menuBGM", 75);

	sf::Sprite* sprite3 = new sf::Sprite();
	sprite3->setTexture(*TextureManager::getInstance()->getTextureByKey("bgMenu"));
	sf::Vector2u textureSize3 = sprite3->getTexture()->getSize();
	sprite3->setOrigin(textureSize3.x / 2, textureSize3.y / 2);
	sprite3->setPosition(0 , (Game::WINDOW_HEIGHT / 2) - 150);

	Renderer* renderer3 = new Renderer("Menu");
	renderer3->assignDrawable(sprite3);
	this->attachComponent(renderer3);

	Sprite* sprite2 = new Sprite();
	sprite2->setTexture(*TextureManager::getInstance()->getTextureByKey("popUpGray"));
	Vector2u textureSize2 = sprite2->getTexture()->getSize();
	sprite2->setOrigin(textureSize2.x / 2, textureSize2.y / 2);

	Renderer* renderer2 = new Renderer("popUp");
	renderer2->assignDrawable(sprite2);
	this->attachComponent(renderer2);

	Sprite* sprite = new Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("menuLogo"));
	Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("MainMenuScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	float posX = Game::WINDOW_WIDTH / 2;
	float posY = Game::WINDOW_HEIGHT / 2;
	this->setPosition(Game::WINDOW_WIDTH / 2, (Game::WINDOW_HEIGHT / 2) - 150);

	Texture* btnNormal = TextureManager::getInstance()->getTextureByKey("buttonSpriteSheet");
	Texture* btnPressed = TextureManager::getInstance()->getTextureByKey("buttonSpriteSheet");

	
	UIButton* button1 = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button1);
	button1->setPosition((Game::WINDOW_WIDTH / 2) - 150, 500);
	button1->getTransformable()->setScale(3.0f, 3.0f);
	button1->setButtonListener(this);
	
	UIText* button_1Text = new UIText("text_1");
	button1->attachChild(button_1Text);
	button_1Text->setPosition(-110, -100);
	button_1Text->setSize(10);
	button_1Text->setText("LEVEL 1");


	UIButton* button2 = new UIButton("button_2", btnNormal, btnPressed);
	this->attachChild(button2);
	button2->setPosition((Game::WINDOW_WIDTH / 2) + 100, 500);
	button2->getTransformable()->setScale(3.0f, 3.0f);
	button2->setButtonListener(this);

	UIText* button_2Text = new UIText("text_2");
	button2->attachChild(button_2Text);
	button_2Text->setPosition(-110, -100);
	button_2Text->setSize(10);
	button_2Text->setText("Quit");

}

void MainMenu::onButtonClick(UIButton* button)
{
	
}

void MainMenu::onButtonReleased(UIButton* button)
{
	if (button->getName() == "button_1")
	{
		SFXManager::getInstance()->getSFX("menuBGM")->stop();
		SceneManager::getInstance()->loadScene(SceneManager::LEVEL1_SCENE_NAME);
	}
	if (button->getName() == "button_2")
	{
		SFXManager::getInstance()->getSFX("menuBGM")->stop();
		ApplicationManager::getInstance()->applicationQuit();
	}
	//std::cout << button->getName();
}

