#include "ApplicationManager.h"

ApplicationManager* ApplicationManager::sharedInstance = NULL;

void ApplicationManager::initialize(sf::RenderWindow* window)
{
	sharedInstance = new ApplicationManager();
	sharedInstance->window = window;
	sharedInstance->state = Running;
}

ApplicationManager* ApplicationManager::getInstance()
{
	return sharedInstance;
}

void ApplicationManager::applicationQuit()
{
	this->window->close();
}

void ApplicationManager::pauseApplication()
{
	this->state = Paused;
}

void ApplicationManager::resumeApplication()
{
	this->state = Running;
}

bool ApplicationManager::isPaused()
{
	if (this->state == Paused)
	{
		return true;
	}
	else
	{
		return false;
	}
}


ApplicationManager::~ApplicationManager()
{
	delete this->window;
}
