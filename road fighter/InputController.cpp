#include "InputController.h"

InputController::InputController(string name) : ObjectComponent(name, Input)
{
	this->type = Input;
}

InputController::~InputController()
{
	ObjectComponent::~ObjectComponent();
}

void InputController::perform()
{
}

void InputController::assignEvent(Event event)
{
	this->event = event;
}
