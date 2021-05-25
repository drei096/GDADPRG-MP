#pragma once
#include "UIButtonInputController.h"
class QuitPopUp : public GameObject, public ButtonListener
{
public:
	QuitPopUp(string name);
	~QuitPopUp();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
};
