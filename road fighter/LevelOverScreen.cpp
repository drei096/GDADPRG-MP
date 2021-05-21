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
	SFXManager::getInstance()->getSFX("gameOverBGM")->play();

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
	button_1Text->setPosition(-20, -80);
	button_1Text->setSize(15);
	button_1Text->setText("GO TO MAIN MENU");

	UIText* displayText = new UIText("displayText");
	this->attachChild(displayText);
	displayText->setPosition(-20, -100);
	displayText->setSize(40);
	displayText->setText("Congratulations!");

}

void LevelOverScreen::onButtonClick(UIButton* button)
{
}

void LevelOverScreen::onButtonReleased(UIButton* button)
{
	SFXManager::getInstance()->getSFX("gameOverBGM")->stop();
	SceneManager::getInstance()->unloadScene();
	SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
	ApplicationManager::getInstance()->resumeApplication();
}
