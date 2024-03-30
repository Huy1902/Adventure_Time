#include "PlayingState.h"

#include "GameManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "StatusManager.h"

#include "PauseState.h"
#include "GameOverState.h"

#include "MapParser.h"

#include "ButtonModel.h"
#include "PlayerObject.h"

const std::string  PlayingState::m_sPlaying = "PLAYING";

void PlayingState::m_sPlayingToPause()
{
	GameManager::getInstance()->getFSM()->pushState(new PauseState());
}

void PlayingState::m_sPlayingToGameOver()
{
	GameManager::getInstance()->getFSM()->changeState(new GameOverState());
}

void PlayingState::processData()
{
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_ESCAPE) == true)
	{
		m_sPlayingToPause();
	}
	if (mPlayer->getStatus()->isAlive == false)
	{
		if (mPlayer->isDying() == true)
		{
			m_bSetupDying = true;
		}
		else
		{
			m_sPlayingToGameOver();
		}
		mPlayer->processData();
		return;
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
	StatusManager::getInstance()->updatePlayerStatus();
}
void PlayingState::renderState()
{
	if (m_bSetupDying == true)
	{
		mPlayer->renderObject();
		return;
	}
	if (mObjects.empty() == false)
	{
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->renderObject();
		}
	}
	mMap->renderMap();
	StatusManager::getInstance()->renderPlayerStatus();
}

bool PlayingState::startState()
{
	mMap = MapParser::getInstance()->parseMap("map1.tmx");
	//mMap->loadMap("map1.txt", "tileset1");

	mPlayer = new PlayerObject();
	mMap->setPlayer(mPlayer);

	StatusManager::getInstance()->setPlayer(mPlayer);

	SoundManager::getInstance()->playMusic("play_theme", -1);

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
