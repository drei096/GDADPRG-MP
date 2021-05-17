#include "Scene.h"
#include "GameObjectManager.h"

Scene::Scene(string sceneName)
{
	this->sceneName = sceneName;
}

Scene::~Scene()
{

}

void Scene::onUnloadObjects()
{
	GameObjectManager::getInstance()->deleteAllObjectsInScene();
}

string Scene::getSceneName()
{
	return this->sceneName;
}

void Scene::registerObject(GameObject* object)
{
	GameObjectManager::getInstance()->addObject(object);
}
