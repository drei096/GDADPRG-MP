#include "UIText.h"
#include "FontManager.h"
#include "Renderer.h"

UIText::UIText(string name) : GameObject(name)
{
	this->text = new Text();
}

UIText::~UIText() 
{
	GameObject::~GameObject();
}

void UIText::initialize()
{
	//declare a text to be used
	//font must be a pointer or else it gets immediately de-allocated.
	Font* font = FontManager::getInstance()->getFont("default");
	text->setFont(*font);
	text->setFillColor(Color::White);
	text->setOutlineColor(Color::Black);
	//text->setOutlineThickness(4.0f);
	this->setSize(40);
	this->setText("<Using placeholder!>");

	Renderer* renderer = new Renderer("Button");
	renderer->assignDrawable(text);
	this->attachComponent(renderer);
}

void UIText::setText(string text) 
{
	this->text->setString(text);
	FloatRect bounds = this->text->getLocalBounds();
	// Align center, you can put other alignment here
	this->text->setOrigin(bounds.width / 2, bounds.height / 2);
}

string UIText::getText() 
{
	return this->text->getString();
}


void UIText::setSize(unsigned int size) 
{
	this->text->setCharacterSize(size);
}
