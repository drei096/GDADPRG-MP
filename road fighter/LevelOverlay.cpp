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
#include "SpeedTextUpdater.h"
#include "SFXManager.h"
#include <iostream>
#include "QuitPopUp.h"

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

	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

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

	FuelTextUpdater* fuelTextUpdate = new FuelTextUpdater("fuel_text_updater");
	fuelText->attachComponent(fuelTextUpdate);


	UIText* speedText = new UIText("speed_text");
	GameObjectManager::getInstance()->addObject(speedText);
	speedText->setPosition((Game::WINDOW_WIDTH / 2) + 300, (Game::WINDOW_HEIGHT / 2) + 175);
	speedText->setSize(20);
	speedText->setText("SPEED \n" + (to_string)(this->speed) + " KM/H");

	SpeedTextUpdater* speedTextUpdate = new SpeedTextUpdater("speed_text_updater");
	speedText->attachComponent(speedTextUpdate);

	sf::Texture* btnNormal = TextureManager::getInstance()->getTextureByKey("buttonSpriteSheet");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTextureByKey("buttonSpriteSheet");

	UIButton* button = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button);
	button->setPosition(475, 375);
	button->getTransformable()->setScale(1.5, 1.5f);
	button->setButtonListener(this);
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
	
	if (button->getName() == "button_1")
	{
		ApplicationManager::getInstance()->pauseApplication();
		QuitPopUp* quitpopUp = new QuitPopUp("quitPopUp");
		GameObjectManager::getInstance()->addObject(quitpopUp);
	}
	
	//std::cout << button->getName();
}
