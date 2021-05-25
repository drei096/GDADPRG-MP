#pragma once
#include "Scene.h"
class Level3PlayScene : public Scene
{
public:
	Level3PlayScene();
	~Level3PlayScene();

	void onLoadResources();
	void onLoadObjects();
	void onUnloadObjects();
	void onUnloadResources();
};

