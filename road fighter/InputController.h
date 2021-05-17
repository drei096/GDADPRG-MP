#pragma once
#include "ObjectComponent.h"

using namespace std;
using namespace sf;

class InputController : public ObjectComponent
{
public:
	InputController(string name);
	~InputController();

	void perform();
	void assignEvent(Event event);

protected:
	Event event;
};

