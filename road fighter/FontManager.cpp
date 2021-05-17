#include "FontManager.h"
#include <iostream>

FontManager* FontManager::sharedInstance = NULL;

FontManager* FontManager::getInstance() 
{
	//initialize only when we need it
	if (sharedInstance == NULL) 
	{
		sharedInstance = new FontManager();
	}
	return sharedInstance;
}

void FontManager::loadAll()
{

	loadFont("default", "Media/Fonts/Sansation.ttf");

}

void FontManager::loadFont(string key, string path) 
{
	sf::Font* font = new sf::Font();
	font->loadFromFile(path);
	fontMap[key] = font;
}

sf::Font* FontManager::getFont(string key) 
{
	if (fontMap[key] != NULL) 
	{
		return fontMap[key];
	}
	else 
	{
		cout << "No font found for " << key;
		return NULL;
	}
}
