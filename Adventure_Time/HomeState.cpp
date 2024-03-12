#include "HomeState.h"
#include "GameManager.h"

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

}
bool HomeState::exitState()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->clearObject();
	}
	mObjects.clear();

}