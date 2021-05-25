#pragma once
#include "GameObject.h"
class BG : public GameObject
{
public:
	BG(std::string name, float _MAX, string _textureKey, int _level);
	void initialize();
	float MAX_DISTANCE;

private:
	const float SPEED_MULTIPLIER = 100.0f;
	string textureKey;
	int level;
};

