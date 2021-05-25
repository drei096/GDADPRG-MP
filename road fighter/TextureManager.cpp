#include "TextureManager.h"
#include <cstddef>
#include <iostream>

TextureManager* TextureManager::sharedInstance = NULL;

TextureManager* TextureManager::getInstance()
{
    if (sharedInstance == NULL)
    {
        sharedInstance = new TextureManager();
    }
    return sharedInstance;
}

void TextureManager::loadAllTextures()
{
    loadTexture("bg1", "Media/Textures/1.png");
    loadTexture("bg2", "Media/Textures/2.png");
    loadTexture("bg3", "Media/Textures/3.png");
    loadTexture("bgMenu", "Media/Textures/bgMenu.png");
    sf::Texture* bgTex;
    bgTex = getTextureByKey("bg1");
    bgTex->setRepeated(true);
    sf::Texture* bgTex2;
    bgTex2 = getTextureByKey("bg2");
    bgTex2->setRepeated(true);
    sf::Texture* bgTex3;
    bgTex3 = getTextureByKey("bg3");
    bgTex3->setRepeated(true);
    loadTexture("player", "Media/Textures/p_car.png");
    //loadTexture("enemyCar", "Media/Textures/GalardB.png");
    loadTexture("menuLogo", "Media/Textures/logo2.png");
    loadTexture("buttonSpriteSheet", "Media/Textures/arcade_buttons.png");
    loadTexture("popUpYellow", "Media/Textures/PopUpTextures/Yellow.png");
    loadTexture("popUpGray", "Media/Textures/PopUpTextures/Gray.png");
    loadTexture("textBoxSpriteSheet", "Media/Textures/ui_greenSheet.png");
    loadTexture("enemyCivCars", "Media/Textures/civ_cars_spritesheet.png");
    loadTexture("roadConditions", "Media/Textures/road_conditions.png");
    loadTexture("oil_slick", "Media/Textures/oil_slick.png");
}

Texture* TextureManager::getTextureByKey(string key)
{
    if (textureMap[key] != NULL)
    {
        return textureMap[key];
    }
    else
    {
        cout << "No texture found for " << key << endl;
        return NULL;
    }
}

void TextureManager::loadTexture(string key, string path)
{
    Texture* texture = new Texture();
    texture->loadFromFile(path);
    textureMap[key] = texture;
}
