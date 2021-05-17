#include "Level1PlayScene.h"
#include "PlayerCar.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "UIText.h"
#include "Renderer.h"

Level1PlayScene::Level1PlayScene() : Scene(SceneManager::LEVEL1_SCENE_NAME)
{
}

Level1PlayScene::~Level1PlayScene()
{
}

void Level1PlayScene::onLoadResources()
{
	UIText* scoreText = new UIText("score_text");
	scoreText->setPosition(-70,-80);
	scoreText->setSize(10);
	scoreText->setText("1P\n 00000000");
}

void Level1PlayScene::onLoadObjects()
{
	PlayerCar* player = new PlayerCar("player");
	this->registerObject(player);
	//GameObjectManager::getInstance()->addObject(player);
}

void Level1PlayScene::onUnloadObjects()
{
	Scene::onUnloadObjects();
}

void Level1PlayScene::onUnloadResources()
{
}
