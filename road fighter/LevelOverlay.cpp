#include "LevelOverlay.h"
#include "TextureManager.h"
#include "Game.h"
#include "Renderer.h"
#include "UIButton.h"
#include "UIText.h"
#include "GameObjectManager.h"
#include "ApplicationManager.h"
#include "SceneManager.h"
#include "ScoreTextUpdater.h"
#include "FuelTextUpdater.h"
#include "SFXManager.h"
#include <iostream>

LevelOverlay::LevelOverlay(string name) : GameObject(name), ButtonListener()
{
}

LevelOverlay::~LevelOverlay()
{
	GameObject::~GameObject();
}

void LevelOverlay::initialize()
{
	SFXManager::getInstance()->play("levelBGM");
	/*
	Sprite* sprite2 = new Sprite();
	sprite2->setTexture(*TextureManager::getInstance()->getTextureByKey("popUpGray"));
	Vector2u textureSize2 = sprite2->getTexture()->getSize();
	sprite2->setOrigin(textureSize2.x / 2, textureSize2.y / 2);

	Renderer* renderer2 = new Renderer("popUp");
	renderer2->assignDrawable(sprite2);
	this->attachComponent(renderer2);
	*/
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);


	/*
	Texture* btnNormal = TextureManager::getInstance()->getTextureByKey("buttonSpriteSheet");
	Texture* btnPressed = TextureManager::getInstance()->getTextureByKey("buttonSpriteSheet");


	UIButton* button1 = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button1);
	button1->setPosition(150, 500);
	button1->getTransformable()->setScale(3.0f, 3.0f);
	button1->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button1->attachChild(button_1Text);
	button_1Text->setPosition(-70, -80);
	button_1Text->setSize(10);
	button_1Text->setText("LEVEL 1");
	*/

	UIText* scoreText = new UIText("score_text");
	GameObjectManager::getInstance()->addObject(scoreText);
	scoreText->setPosition((Game::WINDOW_WIDTH / 2) + 300, (Game::WINDOW_HEIGHT / 2) - 175);
	scoreText->setSize(20);
	scoreText->setText("SCORE\n" + (to_string)(this->score));

	ScoreTextUpdater* scoreTextUpdate = new ScoreTextUpdater("score_text_updater");
	scoreText->attachComponent(scoreTextUpdate);


	UIText* fuelText = new UIText("fuel_text");
	GameObjectManager::getInstance()->addObject(fuelText);
	fuelText->setPosition((Game::WINDOW_WIDTH / 2) + 300, (Game::WINDOW_HEIGHT / 2));
	fuelText->setSize(20);
	fuelText->setText("FUEL \n" + (to_string)(this->fuel));

	FuelTextUpdater* fuelTextUpdate = new FuelTextUpdater("score_text_updater");
	fuelText->attachComponent(fuelTextUpdate);
}


void LevelOverlay::onButtonClick(UIButton* button)
{


	/*
	//std::cout << button->getName();

	if (button->getName() == "button_1")
	{
		exit(0);
	}
	if (button->getName() == "button_2")
	{
		GameObjectManager::getInstance()->deleteObjectByName("LevelOverlayScreen");
		ApplicationManager::getInstance()->resumeApplication();
	}
	*/
}

void LevelOverlay::onButtonReleased(UIButton* button)
{
	/*
	if (button->getName() == "button_1")
	{
		SceneManager::getInstance()->loadScene(SceneManager::LEVEL1_SCENE_NAME);
	}
	*/
	//std::cout << button->getName();
}
