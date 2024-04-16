#include "IntroState.h"

#include "InputManager.h"
#include "VideoPlayer.h"
#include "GameManager.h"
#include "HomeState.h"
const std::string IntroState::m_sGameLoading = "INTRO";



IntroState::IntroState()
{
}

IntroState::~IntroState()
{
}

void IntroState::processData()
{
	if (InputManager::getInstance()->isPressAnyKey())
	{
		fromIntroToHome();
	}
	VideoPlayer::getInstance()->updateFrame();
}
void IntroState::renderState()
{
	VideoPlayer::getInstance()->renderFrame();
}

bool IntroState::startState()
{
	//ObjectParser::getInstance()->parserButton("game_over_state.xml", mButton, mTexture);
	//for (const auto& ite : mTexture)
	//{
	//	TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	//}
	//for (const auto& ite : mButton)
	//{
	//	ButtonModel* obj = new ButtonModel();
	//	obj->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader(ite.textureID, ite.x, ite.y, ite.w, ite.h, ite.numFrames, ite.callbackID)));
	//	obj->setCallback(mCallback[ite.callbackID]);
	//	mObjects.push_back(obj);
	//}
	VideoPlayer::getInstance()->setFilePath("assets/Intro/intro", 349);
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
