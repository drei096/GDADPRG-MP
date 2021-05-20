#pragma once
#include "GameObject.h"
#include "UIButtonInputController.h"
class ProgressBar : public GameObject, public ButtonListener
{
public:
	ProgressBar(string name);
	~ProgressBar();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
	int laps = 1;
};

