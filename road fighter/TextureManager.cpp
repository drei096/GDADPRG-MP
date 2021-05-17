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
    loadTexture("player", "Media/Textures/p_car.png");
    loadTexture("menuLogo", "Media/Textures/logo.jpeg");
    loadTexture("buttonSpriteSheet", "Media/Textures/arcade_buttons.png");
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
