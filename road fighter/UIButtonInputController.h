#pragma once
#include "InputController.h"
#include "ButtonListener.h"
#include "UIButton.h"

class UIButtonInputController : public InputController
{
public:
	UIButtonInputController(string name, ButtonListener* buttonListener);
	~UIButtonInputController();

	void perform();

private:
	ButtonListener* buttonListener;
	bool pressed = false;
};




