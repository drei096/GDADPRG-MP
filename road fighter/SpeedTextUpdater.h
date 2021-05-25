#pragma once
#include "ObjectComponent.h"
class SpeedTextUpdater : public ObjectComponent
{
public:
	SpeedTextUpdater(string name);
	~SpeedTextUpdater();

	void perform();
};

