#include "IntroState.h"

#include "InputManager.h"
#include "VideoPlayer.h"
#include "GameManager.h"
#include "HomeState.h"
#include "FontManager.h"
#include "Cursor.h"
const std::string IntroState::m_sGameLoading = "INTRO";



IntroState::IntroState()
{
}

IntroState::~IntroState()
{
}

void IntroState::processData()
{
	if (InputManager::getInstance()->isPressAnyKey() == true || InputManager::getInstance()->getMouseButton(LEFT) == true)
	{
		fromIntroToHome();
	}
	VideoPlayer::getInstance()->updateFrame();
}
void IntroState::renderState()
{
	VideoPlayer::getInstance()->renderFrame();
	FontManager::getInstance()->drawText("Press any key to continue", 440, 690, 24);
}

bool IntroState::startState()
{
	VideoPlayer::getInstance()->setFilePath("assets/Intro/intro", 1049, "intro");
	Cursor::getInstance()->render();
	return true;
}
bool IntroState::exitState()
{
	return true;
}

void IntroState::fromIntroToHome()
{
	GameManager::getInstance()->getFSM()->changeState(new HomeState());
}
