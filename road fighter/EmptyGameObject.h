#pragma once
#include "GameObject.h"
class EmptyGameObject : public GameObject
{
public:
	EmptyGameObject(string name);
	~EmptyGameObject();
	void initialize();
};

