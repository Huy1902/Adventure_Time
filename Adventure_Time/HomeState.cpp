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
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->processData();
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
	TextureManager::getInstance()->load("assets/exit_button.png", "exit_button", GameManager::getInstance()->getRenderer());


	ButtonModel* play = new ButtonModel();
	play->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("play_button", 300, 300, 250, 80, 3, 1.0)));
	play->setCallback(m_sHomeToPlay);

	ButtonModel* exit = new ButtonModel();
	exit->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("exit_button", 300, 500, 250, 80, 3, 1.0)));
	exit->setCallback(m_sExitHome);

	mObjects.push_back(play);
	mObjects.push_back(exit);
	mTextureID.push_back("play_button");
	mTextureID.push_back("exit_button");
	return true;
}
bool HomeState::exitState()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->clearObject();
		delete mObjects[i];
	}
	for (size_t i = 0; i < mTextureID.size(); ++i)
	{
		TextureManager::getInstance()->clearFromTexture(mTextureID[i]);
	}
	mTextureID.clear();
	mObjects.clear();

	return true;
}