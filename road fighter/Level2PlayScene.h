#pragma once
#include "Scene.h"
class Level2PlayScene : public Scene
{
public:
	Level2PlayScene();
	~Level2PlayScene();

	void onLoadResources();
	void onLoadObjects();
	void onUnloadObjects();
	void onUnloadResources();
};

