#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include "Game.h"
#include "GameObject.h"
class Scene
{
public:
	Scene(string sceneName);
	~Scene();

	virtual void onLoadResources() = 0;
	virtual void onLoadObjects() = 0;

	virtual void onUnloadResources() = 0;
	virtual void onUnloadObjects();

	string getSceneName();

protected:
	void registerObject(GameObject* object); //IMPORTANT: This must be called for every object to be loaded/unloaded.
	string sceneName;
};

