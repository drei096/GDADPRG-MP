#pragma once
#include "UIButtonInputController.h"
class NoFuelScreen : public GameObject, public ButtonListener
{
public:
	NoFuelScreen(string name);
	~NoFuelScreen();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
};

