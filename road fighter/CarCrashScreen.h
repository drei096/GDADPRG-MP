#pragma once
#include "UIButtonInputController.h"
class CarCrashScreen : public GameObject, public ButtonListener
{
public:
	CarCrashScreen(string name);
	~CarCrashScreen();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
};

