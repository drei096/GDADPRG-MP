#pragma once
#include "GameObject.h"

class UIText : public GameObject
{
public:
	UIText(string name);
	~UIText();
	void initialize();
	void setText(string text);
	string getText();
	void setSize(unsigned int size);
private:
	Text* text;
};



