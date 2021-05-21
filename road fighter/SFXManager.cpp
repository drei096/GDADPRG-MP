#include <SFML/Audio.hpp>
#include <iostream>
#include <cstddef>
#include "SFXManager.h"

SFXManager* SFXManager::sharedInstance = NULL;

SFXManager* SFXManager::getInstance() {
	//initialize only when we need it
	if (sharedInstance == NULL) {
		sharedInstance = new SFXManager();
	}
	return sharedInstance;
}

void SFXManager::loadAllSFX() {
	//BGM LOADING
	loadSFX("menuBGM", "Media/Sounds/BGM/EveryDay.ogg");
	SFXManager::getInstance()->getSFX("menuBGM")->setLoop(true);
	loadSFX("levelBGM", "Media/Sounds/BGM/Black-Diamond.ogg");
	SFXManager::getInstance()->getSFX("levelBGM")->setLoop(true);
	loadSFX("gameOverBGM", "Media/Sounds/BGM/designate_patreon.ogg");
	SFXManager::getInstance()->getSFX("gameOverBGM")->setLoop(true);

	//SFX LOADING
	loadSFX("collide", "Media/Sounds/SFX/collide.ogg");
	loadSFX("explode", "Media/Sounds/SFX/explode.wav");
	loadSFX("glassbreak", "Media/Sounds/SFX/glass_break.wav");
	loadSFX("beep", "Media/Sounds/SFX/beep.ogg");

}

void SFXManager::loadSFX(string key, string path) {
	SoundBuffer* SFX = new sf::SoundBuffer();
	SFX->loadFromFile(path);
	Sound* sound = new sf::Sound();
	sound->setBuffer(*SFX);
	SFXMap[key] = sound;
}

sf::Sound* SFXManager::getSFX(std::string key) {
	if (SFXMap[key] != NULL) {
		return SFXMap[key];
	}
	else {
		std::cout << "No SFX found for " << key;
		return NULL;
	}
}