#include "HomeState.h"

#include "GameManager.h"
#include "ObjectModel.h"
#include "TextureManager.h"
#include "ButtonModel.h"
#include "PlayingState.h"

const std::string  HomeState::m_sHomeID = "HOME";

void HomeState::m_sHomeToPlay()
{
	GameManager::getInstance()->getFSM()->changeState(new PlayingState());
}

void HomeState::m_sExitHome()
{
	GameManager::getInstance()->quitGame();
}

void HomeState::processData()
{
	if (!mObjects.empty())
	{
		for (ObjectModel* ite: mObjects)
		{
			ite->processData();
			if (mObjects.empty())
			{
				break;
			}
		}
	}
}
void HomeState::renderState()
{
	if (mObjects.empty() == false)
	{
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->renderObject();
		}
	}
}

bool HomeState::startState()
{
	TextureManager::getInstance()->load("assets/play_button.png", "play_button", GameManager::getInstance()->getRenderer());

	ButtonModel* play = new ButtonModel();
	play->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("play_button", 300, 300, 250, 80, 3, 1.0)));
	play->setCallback(m_sHomeToPlay);


	mObjects.push_back(play);
	return true;
}
bool HomeState::exitState()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->clearObject();
		delete mObjects[i];
	}
	mObjects.clear();
	return true;
}