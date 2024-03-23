#include "PlayingState.h"

#include "GameManager.h"
#include "TextureManager.h"
#include "InputManager.h"

#include "PlayerObject.h"

#include "PauseState.h"
#include "HomeState.h"

#include "ButtonModel.h"

const std::string  PlayingState::m_sPlaying = "PLAYING";

void PlayingState::m_sPlayingToPause()
{
	GameManager::getInstance()->getFSM()->pushState(new PauseState());
}

//void PlayingState::m_sPlayingToHome()
//{
//	GameManager::getInstance()->getFSM()->changeState(new HomeState());
//}

void PlayingState::processData()
{
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_ESCAPE) == true)
	{
		m_sPlayingToPause();
	}
	if (mObjects.empty() == false)
	{
		for (int i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->processData();
			if (mObjects.empty())
			{
				break;
			}
		}
	}
	mMap->updateMap();
}
void PlayingState::renderState()
{
	if (mObjects.empty() == false)
	{
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->renderObject();
		}
	}
	mMap->renderMap();
}

bool PlayingState::startState()
{
	mMap = new Map();
	mMap->loadMap("map1.txt", "tileset1");

	mPlayer = new PlayerObject();
	mMap->setPlayer(mPlayer);

	//mObjects.push_back(player);
	return true;
}
bool PlayingState::exitState()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->clearObject();
		delete mObjects[i];
	}
	mTextureID.clear();
	mObjects.clear();
	delete mMap;
	delete mPlayer;
	return true;
}
