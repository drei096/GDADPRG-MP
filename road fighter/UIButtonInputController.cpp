#include "UIButtonInputController.h"
#include <iostream>

UIButtonInputController::UIButtonInputController(string name, ButtonListener* buttonListener) : InputController(name)
{
	this->buttonListener = buttonListener;
}

UIButtonInputController::~UIButtonInputController()
{
	ObjectComponent::~ObjectComponent();
}

void UIButtonInputController::perform() 
{

	UIButton* button = (UIButton*)this->getOwner();
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && this->pressed) 
	{
		this->pressed = false;
		button->changeButtonToNormal();
		this->buttonListener->onButtonReleased(button);
	}

	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
	{
		//check if button is within mouse coord
		sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
		sf::FloatRect bounds = button->getGlobalBounds();

		if (bounds.contains(mousePos)) 
		{
			this->pressed = true;
			button->changeButtonToPressed();
			this->buttonListener->onButtonClick(button);
		}
	}


}
