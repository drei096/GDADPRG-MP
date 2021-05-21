#include "ScoreTextUpdater.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Game.h"
#include "CarProgressMovement.h"
#include "ProgressBar.h"
#include "UIText.h"
#include "LevelOverlay.h"
#include <iostream>
#include "PhysicsManager.h"

ScoreTextUpdater::ScoreTextUpdater(string name) : ObjectComponent(name, Script)
{
}

ScoreTextUpdater::~ScoreTextUpdater()
{
	ObjectComponent::~ObjectComponent();
}

void ScoreTextUpdater::perform()
{
	UIText* textScore = (UIText*)GameObjectManager::getInstance()->findObjectByName("score_text");
	LevelOverlay* levelOverlay = (LevelOverlay*)GameObjectManager::getInstance()->findObjectByName("levelOverlay");
	ProgressBar* carProgress = (ProgressBar*)GameObjectManager::getInstance()->findObjectByName("progressBar");

	if (textScore == NULL || levelOverlay == NULL || carProgress == NULL)
	{
		cout << "One or more of the needed dependencies are missing!\n";
		return;
	}

	//cout << collisionCount << endl;
	//cout << carProgress->laps << endl;

	/*
	if (player->getTransformable()->getPosition().y < redCar->getTransformable()->getPosition().y)
	{
		levelOverlay->score += 50;
	}
	*/

	int laps = carProgress->laps;

	levelOverlay->score = (laps - 1) * 50;

	textScore->setText("SCORE\n" + (to_string)(levelOverlay->score));

}
