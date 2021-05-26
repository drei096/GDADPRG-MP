#include "LevelOverScreen.h"
#include "UIText.h"
#include "TextureManager.h"
#include "Game.h"
#include "UIButton.h"
#include "ApplicationManager.h"
#include "GameObjectManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "PhysicsManager.h"
#include "SFXManager.h"
#include "Level1PlayScene.h"
#include "BGMovement.h"
#include "GameObject.h"

LevelOverScreen::LevelOverScreen(string name) : GameObject(name), ButtonListener()
{

}

LevelOverScreen::~LevelOverScreen()
{
	GameObject::~GameObject();
}

void LevelOverScreen::initialize()
{
	SFXManager::getInstance()->getSFX("levelBGM")->stop();
	SFXManager::getInstance()->play("level_endBGM");

	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("textBoxSpriteSheet"));

	sprite->setTextureRect(sf::IntRect(0, 0, 190, 50));
	sprite->setScale(2.5, 2.5);

	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);
	sprite->setPosition(Game::WINDOW_WIDTH / 2 , Game::WINDOW_HEIGHT / 2 - 100);

	Renderer* renderer = new Renderer("LevelOverScreen");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	sf::Texture* btnNormal = TextureManager::getInstance()->getTextureByKey("buttonSpriteSheet");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTextureByKey("buttonSpriteSheet");

	UIButton* button = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button);
	button->setPosition(0, 70);
	button->getTransformable()->setScale(1.5, 1.5f);
	button->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button->attachChild(button_1Text);
	button_1Text->setPosition(0, -80);
	button_1Text->setSize(15);
	button_1Text->setText("CONTINUE");

	UIText* displayText = new UIText("displayText");
	this->attachChild(displayText);
	displayText->setPosition(-20, -100);
	displayText->setSize(30);
	displayText->setText("Congratulations!");

}

void LevelOverScreen::onButtonClick(UIButton* button)
{
	SFXManager::getInstance()->getSFX("level_endBGM")->stop();
}

void LevelOverScreen::onButtonReleased(UIButton* button)
{
	if (button->getName() == "button_1") {
		BGMovement* bgMove = (BGMovement*)GameObjectManager::getInstance()->findObjectByName("BG")->findComponentByName("BG_Movement");
		//if level is 1, load next level
		if (bgMove->level == 1) {
			SceneManager::getInstance()->unloadScene();
			SceneManager::getInstance()->loadScene(SceneManager::LEVEL2_SCENE_NAME);
			ApplicationManager::getInstance()->resumeApplication();
		}
		//if level is 2, load next level
		else if (bgMove->level == 2) {
			SceneManager::getInstance()->unloadScene();
			SceneManager::getInstance()->loadScene(SceneManager::LEVEL3_SCENE_NAME);
			ApplicationManager::getInstance()->resumeApplication();
		}
		//if level is 3, return to menu
		else if (bgMove->level == 3) {
			SceneManager::getInstance()->unloadScene();
			SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
			ApplicationManager::getInstance()->resumeApplication();
		}
	}
	
}
