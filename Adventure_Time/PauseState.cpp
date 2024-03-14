#include "PauseState.h"


#include "GameManager.h"
#include "TextureManager.h"

#include "ButtonModel.h"

#include "HomeState.h"
#include "PlayingState.h"

const std::string  PauseState::m_sPause = "PAUSE";

void PauseState::m_sPauseToHome()
{
	GameManager::getInstance()->getFSM()->changeState(new HomeState());
}

void PauseState::m_sPauseToPlay()
{
	GameManager::getInstance()->getFSM()->popState();
}

void PauseState::processData()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->processData();
	}
}
void PauseState::renderState()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->renderObject();
	}
}

bool PauseState::startState()
{
	TextureManager::getInstance()->load("assets/exit_button.png", "exit_button", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/resume_button.png", "resume_button", GameManager::getInstance()->getRenderer());


	ButtonModel* resume = new ButtonModel();
	resume->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("resume_button", 300, 300, 250, 80, 3, 1.0)));
	resume->setCallback(m_sPauseToPlay);

	ButtonModel* exit = new ButtonModel();
	exit->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("exit_button", 300, 500, 250, 80, 3, 1.0)));
	exit->setCallback(m_sPauseToHome);

	mObjects.push_back(resume);
	mObjects.push_back(exit);
	return true;
}
bool PauseState::exitState()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->clearObject();
	}
	mObjects.clear();
	return true;
}