#include "HomeState.h"

#include "GameManager.h"
#include "ObjectModel.h"
#include "TextureManager.h"
#include "ButtonModel.h"

const std::string  HomeState::m_sHomeID = "HOME";

void HomeState::m_sHomeToPlay()
{
	//GameManager::getInstance()->getFSM()->changeState(new PlayState());
}

void HomeState::m_sExitHome()
{
	GameManager::getInstance()->quitGame();
}

void HomeState::processData()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->processData();
	}
}
void HomeState::renderState()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->renderObject();
	}
}

bool HomeState::startState()
{
	TextureManager::getInstance()->load("assets/play_button.png", "play_button", GameManager::getInstance()->getRenderer());

	ButtonModel* play = new ButtonModel();
	play->loadTexture(std::unique_ptr<TextureLoader> (new TextureLoader("play_button", 300, 300, 250, 80, 3, 1.0)));
	play->setCallback(m_sHomeToPlay);

	mObjects.push_back(play);
	return true;
}
bool HomeState::exitState()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->clearObject();
	}
	mObjects.clear();
	return true;
}