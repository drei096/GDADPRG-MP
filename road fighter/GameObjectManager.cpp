#include "GameObjectManager.h"
#include <iostream>

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance() {
	if (sharedInstance == NULL) {
		sharedInstance = new GameObjectManager();
	}

	return sharedInstance;
}

GameObject* GameObjectManager::findObjectByName(string name) 
{
	if (gameObjectMap[name] != NULL) 
	{
		return gameObjectMap[name];
	}
	else 
	{
		cout << "object " << name << " not found!";
		return NULL;
	}
}

List GameObjectManager::getAllObjects() 
{
	return gameObjectList;
}

int GameObjectManager::activeObjects() 
{
	return gameObjectList.size();
}


void GameObjectManager::processInput(sf::Event event) 
{
	for (int i = 0; i < gameObjectList.size(); i++) 
	{
		gameObjectList[i]->processInput(event);
	}
}

void GameObjectManager::update(sf::Time deltaTime) 
{
	for (int i = 0; i < gameObjectList.size(); i++) 
	{
		gameObjectList[i]->update(deltaTime);
	}
}


void GameObjectManager::draw(RenderWindow* window) 
{
	for (int i = 0; i < gameObjectList.size(); i++) 
	{
		gameObjectList[i]->draw(window, RenderStates::Default);
	}
}

void GameObjectManager::addObject(GameObject* gameObject)
{
	gameObjectMap[gameObject->getName()] = gameObject;
	gameObjectList.push_back(gameObject);
	gameObject->initialize();
}


void GameObjectManager::deleteObject(GameObject* gameObject)
{
	string key = gameObject->getName();
	delete gameObject;
	gameObjectMap.erase(key);
	gameObjectList.erase(remove(gameObjectList.begin(), gameObjectList.end(), gameObject), gameObjectList.end());
	gameObjectList.shrink_to_fit();
}

void GameObjectManager::deleteObjectByName(string name) 
{
	GameObject* object = findObjectByName(name);

	if (object != NULL) 
	{
		deleteObject(object);
	}
}

void GameObjectManager::deleteAllObjectsInScene()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		delete this->gameObjectList[i];
	}

	this->gameObjectList.clear(); this->gameObjectList.shrink_to_fit();
	this->gameObjectMap.clear();
}

