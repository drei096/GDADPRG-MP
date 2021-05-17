#include "MainMenuScene.h"
#include "MainMenu.h"

MainMenuScene::MainMenuScene() : Scene("MainMenuScene")
{
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::onLoadResources()
{
}

void MainMenuScene::onLoadObjects()
{
	MainMenu* mainMenu = new MainMenu("mainMenu");
	this->registerObject(mainMenu);
}

void MainMenuScene::onUnloadResources()
{
}
