#include "PlayingState.h"

#include "GameManager.h"
#include "TextureManager.h"
#include "InputManager.h"

#include "PlayerObject.h"

#include "PauseState.h"
#include "HomeState.h"

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