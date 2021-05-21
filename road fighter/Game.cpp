#include "Game.h"
#include "TextureManager.h""
#include <SFML/Graphics.hpp>
#include "GameObjectManager.h"
#include "ApplicationManager.h"
#include "PlayerCar.h"
#include "FontManager.h"
#include "MainMenu.h"
#include "Scene.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "SFXManager.h"
#include "Level1PlayScene.h"


Game::Game() : window(VideoMode(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT), "Road Fighter")
{
    TextureManager::getInstance()->loadAllTextures();
    FontManager::getInstance()->loadAll();
    SFXManager::getInstance()->loadAllSFX();

    ApplicationManager::getInstance()->initialize(&this->window);

    SceneManager::getInstance()->registerScene(new MainMenuScene());
    SceneManager::getInstance()->loadScene(SceneManager::MAIN_MENU_SCENE_NAME);

    SceneManager::getInstance()->registerScene(new Level1PlayScene());
    
    //PlayerCar* player = new PlayerCar("player");
    //GameObjectManager::getInstance()->addObject(player);
};


void Game::run()
{
    if (ApplicationManager::getInstance()->isPaused() == false)
    {
        Clock clock;
        Time timeSinceLastUpdate = Time::Zero;
        while (window.isOpen()) {

            processEvents();
            timeSinceLastUpdate += clock.restart();
            while (timeSinceLastUpdate > timePerFrame) {
                timeSinceLastUpdate -= timePerFrame;
                processEvents();
                update(timePerFrame);
            }
            render();
            SceneManager::getInstance()->checkLoadScene();
        }
    }

}


void Game::processEvents() {

    Event event;
    while (window.pollEvent(event)) {

        switch (event.type) {
        case Event::Closed:
            window.close();
            break;
        default:
            GameObjectManager::getInstance()->processInput(event);
            break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    if (ApplicationManager::getInstance()->isPaused() == false)
    {
        GameObjectManager::getInstance()->update(deltaTime);
    }
}

void Game::render()
{
    window.clear();
    GameObjectManager::getInstance()->draw(&window);
    window.display();

}


