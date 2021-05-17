#pragma once
#include "Scene.h"
class Level1PlayScene : public Scene
{
public:
	Level1PlayScene();
	~Level1PlayScene();

	void onLoadResources();
	void onLoadObjects();
	void onUnloadObjects();
	void onUnloadResources();
};

