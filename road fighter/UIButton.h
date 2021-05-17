#pragma once
#include "GameObject.h"
#include "ButtonListener.h"

class UIButton : public GameObject
{
public:
	UIButton(string name, Texture* normalTexture, Texture* pressedTexture);
	~UIButton();
	void initialize();
	void changeButtonToNormal();
	void changeButtonToPressed();
	FloatRect getLocalBounds();
	FloatRect getGlobalBounds();
	void setButtonListener(ButtonListener* listener);
private:
	Texture* normalTexture;
	Texture* pressedTexture;
	Sprite* sprite;
	ButtonListener* listener;
};

