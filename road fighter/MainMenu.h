#pragma once
#include "GameObject.h"
#include "UIButton.h"
//ui button here

using namespace std;
using namespace sf;

class MainMenu : public GameObject, public ButtonListener
{
public:
	MainMenu(string name);
	~MainMenu();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);

};

