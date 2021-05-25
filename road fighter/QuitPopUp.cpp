#include "QuitPopUp.h"
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

QuitPopUp::QuitPopUp(string name) : GameObject(name), ButtonListener()
{

}

QuitPopUp::~QuitPopUp()
{
	GameObject::~GameObject();
}

void QuitPopUp::initialize()
{
	SFXManager::getInstance()->getSFX("levelBGM")->pause();

	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*TextureManager::getInstance()->getTextureByKey("popUpGray"));

	sprite->setScale(0.8, 0.8);
	sprite->setColor(sf::Color::Green);

	sf::Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);
	this->setPosition(Game::WINDOW_WIDTH / 2, Game::WINDOW_HEIGHT / 2);

	Renderer* renderer = new Renderer("QuitPopUp");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);

	sf::Texture* btnNormal = TextureManager::getInstance()->getTextureByKey("buttonSpriteSheet");
	sf::Texture* btnPressed = TextureManager::getInstance()->getTextureByKey("buttonSpriteSheet");

	UIButton* button = new UIButton("button_1", btnNormal, btnPressed);
	this->attachChild(button);
	button->setPosition(20, 150);
	button->getTransformable()->setScale(1.5, 1.5f);
	button->setButtonListener(this);

	UIText* button_1Text = new UIText("text_1");
	button->attachChild(button_1Text);
	button_1Text->setPosition(-75, -80);
	button_1Text->setSize(15);
	button_1Text->setText("Yes");

	UIButton* button2 = new UIButton("button_2", btnNormal, btnPressed);
	this->attachChild(button2);
	button2->setPosition(240, 150);
	button2->getTransformable()->setScale(1.5, 1.5f);
	button2->setButtonListener(this);

	UIText* button_2Text = new UIText("text_2");
	button2->attachChild(button_2Text);
	button_2Text->setPosition(-75, -80);
	button_2Text->setSize(15);
	button_2Text->setText("No");

	UIText* displayText = new UIText("displayText");
	this->attachChild(displayText);
	displayText->setPosition(0, -40);
	displayText->setSize(25);
	displayText->setText("Do you want\n to quit?");

}

void QuitPopUp::onButtonClick(UIButton* button)
{

}

void QuitPopUp::onButtonReleased(UIButton* button)
{
	if (button->getName() == "button_1")
	{
		SFXManager::getInstance()->getSFX("levelBGM")->stop();
		SceneManager::getInstance()->unloadScene();
		SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);
		ApplicationManager::getInstance()->resumeApplication();
	}
	else if (button->getName() == "button_2")
	{
		SFXManager::getInstance()->getSFX("levelBGM")->play();
		ApplicationManager::getInstance()->resumeApplication();
		GameObjectManager::getInstance()->deleteObject(this);
	}
}
