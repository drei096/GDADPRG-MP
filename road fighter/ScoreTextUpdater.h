#pragma once
#include "ObjectComponent.h"
class ScoreTextUpdater : public ObjectComponent
{
public:
	ScoreTextUpdater(string name);
	~ScoreTextUpdater();

	void perform();
};

