#pragma once
#include "Scene.h"
class MainMenuScene : public Scene
{
public:
	MainMenuScene();
	~MainMenuScene();
	
	void onLoadResources();
	void onLoadObjects();
	void onUnloadResources();
};

