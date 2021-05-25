#pragma once
#include "GameObject.h"
#include "UIButton.h"
//ui button here

using namespace std;
using namespace sf;

class LevelOverlay : public GameObject, public ButtonListener
{
public:
	LevelOverlay(string name);
	~LevelOverlay();

	void initialize();
	void onButtonClick(UIButton* button);
	void onButtonReleased(UIButton* button);
	int score = 0;
	int fuel = 100;
	int speed = 0;

};

