#include "UIButton.h"
#include "TextureManager.h"
#include <iostream>
#include "Renderer.h"
#include "UIButtonInputController.h"


UIButton::UIButton(string name, Texture* normalTexture, Texture* pressedTexture) : GameObject(name)
{
	this->normalTexture = normalTexture;
	this->pressedTexture = pressedTexture;
}

UIButton::~UIButton()
{
	GameObject::~GameObject();
}

void UIButton::initialize()
{
	sprite = new Sprite();
	sprite->setTexture(*this->normalTexture);
	sprite->setTextureRect(sf::IntRect(0, 0, 32, 32));

	Vector2u textureSize = sprite->getTexture()->getSize();
	sprite->setOrigin(textureSize.x / 2, textureSize.y / 2);

	Renderer* renderer = new Renderer("Button");
	renderer->assignDrawable(sprite);
	this->attachComponent(renderer);
}

void UIButton::setButtonListener(ButtonListener* listener)
{
	//assign input controller
	this->listener = listener;
	UIButtonInputController* inputController = new UIButtonInputController("UI_InputController", this->listener);
	this->attachComponent(inputController);
}

void UIButton::changeButtonToNormal()
{
	this->sprite->setTexture(*this->normalTexture);

}

void UIButton::changeButtonToPressed()
{
	//STILL BUGGY, DOES NOT RETURN TO NORMAL TEXTURE
	this->sprite->setTexture(*this->pressedTexture);
	this->sprite->setTextureRect(sf::IntRect(32, 0, 32, 32));
	
}

sf::FloatRect UIButton::getLocalBounds() {
	return this->sprite->getLocalBounds();
}

sf::FloatRect UIButton::getGlobalBounds() {
	FloatRect bounds = this->sprite->getGlobalBounds();
	//Transform transform;

	//insert calculation for global bounds here

	GameObject* parentObj = this;
	vector<GameObject*> parentList;
	while (parentObj != NULL) {
		parentList.push_back(parentObj);
		parentObj = parentObj->getParent();
	}

	sf::Transform transform = sf::Transform::Identity;
	int startIdx = parentList.size() - 1;
	for (int i = startIdx; i >= 0; i--) {
		transform = transform * parentList[i]->getTransformable()->getTransform();
	}


	bounds = transform.transformRect(bounds);

	// Debug for bound values
	std::cout << endl;
	std::cout << this->name << endl;
	std::cout << bounds.left << " : " << bounds.width << endl;
	std::cout << bounds.top << " : " << bounds.height << endl;
	return bounds;

}
