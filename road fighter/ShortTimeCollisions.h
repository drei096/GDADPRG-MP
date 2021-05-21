#pragma once
#include "ObjectComponent.h"
class ShortTimeCollisions : public ObjectComponent
{
public:
	ShortTimeCollisions(string name);
	~ShortTimeCollisions();

	void perform();
	float ticks = 0;

};

