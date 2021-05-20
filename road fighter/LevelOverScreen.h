#pragma once
#include "UIButtonInputController.h"
class LevelOverScreen : public GameObject, public ButtonListener
{
public:
	LevelOverScreen(string name);
	~LevelOverScreen();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
};

