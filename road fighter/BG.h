#pragma once
#include "GameObject.h"
class BG : public GameObject
{
public:
	BG(std::string name);
	void initialize();
private:
	const float SPEED_MULTIPLIER = 100.0f;
};

