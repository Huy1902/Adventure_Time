#include "PlayingState.h"

#include "GameManager.h"
#include "ObjectModel.h"
#include "TextureManager.h"
#include "PlayerObject.h"

const std::string  PlayingState::m_sPlaying = "PLAING";

void PlayingState::m_sHomeToPlay()
{
	//GameManager::getInstance()->getFSM()->changeState(new PlayState());
}

void PlayingState::m_sExitHome()
{
	GameManager::getInstance()->quitGame();
}

void PlayingState::processData()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->processData();
	}
}
void PlayingState::renderState()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->renderObject();
	}
}

bool PlayingState::startState()
{
	TextureManager::getInstance()->load("assets/knight_player/Idle_KG_1.png", "idle", GameManager::getInstance()->getRenderer());

	PlayerObject* player = new PlayerObject();
	player->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("idle", 100, 600, 100, 64, 4, 1.0)));


	mObjects.push_back(player);
	return true;
}
bool PlayingState::exitState()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->clearObject();
	}
	mObjects.clear();
	return true;
}