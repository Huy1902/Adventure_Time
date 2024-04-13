#include "PlayingState.h"

#include "GameManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "StatusManager.h"

#include "PauseState.h"
#include "GameOverState.h"

#include "InteractManager.h"
#include "MapManager.h"
#include "AchieveManager.h"

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
	AchieveManager::getInstance()->updateAchieve();
	if (m_bSetupRevive == true)
	{
		mMap->setPosition(*InteractManager::getInstance()->getSavedMapPos());
		MapManager::getInstance()->getPlayer()->setPosition(*InteractManager::getInstance()->getSavedPlayerPos());
		MapManager::getInstance()->getPlayer()->getAnimation()->setPosition(*InteractManager::getInstance()->getSavedPlayerPos());
	//	std::cout << MapManager::getInstance()->getPlayer()->getPosition()->getX() << '\n';
		m_bSetupRevive = false;
	}
	if (MapManager::getInstance()->getPlayer()->getStatus()->isAlive == false)
	{
		if (MapManager::getInstance()->getPlayer()->isDying() == true)
		{
			m_bSetupDying = true;
		}
		else
		{
			m_sPlayingToGameOver();
		}
		MapManager::getInstance()->getPlayer()->processData();
		return;
	}

	mMap->updateMap();
	mBackground->updateBackground();
	StatusManager::getInstance()->updatePlayerStatus();
}

void PlayingState::renderState()
{
	mBackground->drawBackground();
	//if (m_bSetupDying == true)
	//{
	//	MapManager::getInstance()->getPlayer()->renderObject();
	//	return;
	//}
	mMap->renderMap();
	StatusManager::getInstance()->renderPlayerStatus();
	AchieveManager::getInstance()->renderAchieve();
}

bool PlayingState::startState()
{
	mMap = MapManager::getInstance()->getCurrentMap();
	mMap->initGround();
	mMap->setPlayer(MapManager::getInstance()->getPlayer());

	StatusManager::getInstance()->setPlayer(MapManager::getInstance()->getPlayer());
	mMap->setPosition(*InteractManager::getInstance()->getSavedMapPos());
	MapManager::getInstance()->getPlayer()->setPosition(*InteractManager::getInstance()->getSavedPlayerPos());
	MapManager::getInstance()->getPlayer()->getAnimation()->setPosition(*InteractManager::getInstance()->getSavedPlayerPos());
	SoundManager::getInstance()->playMusic("play_theme", -1);

	m_bSetupRevive = false;

	mBackground = new Background();

	//SDL_ShowCursor(SDL_DISABLE);
	return true;
}
bool PlayingState::exitState()
{
	//SDL_ShowCursor(SDL_ENABLE);
	mTextureID.clear();
	mObjects.clear();
	delete mBackground;
	//delete mMap;
	return true;
}