#include "PauseState.h"

#include "GameManager.h"
#include "ObjectModel.h"
#include "TextureManager.h"
#include "ButtonModel.h"
#include "PlayingState.h"

#include "ObjectParser.h"

#include "SoundManager.h"

#include "HomeState.h"
#include "PlayingState.h"

#include "StatusManager.h"

const std::string PauseState::m_sPauseID = "Pause";



PauseState::PauseState()
{
	mCallback.push_back(m_sPauseToHome);
	mCallback.push_back(m_sPauseToPlay);

	background = new Background();
	TextureManager::getInstance()->load("assets/button/pause_game_font.png", "pause_game_font", GameManager::getInstance()->getRenderer());
	font = new ObjectModel();
	font->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("pause_game_font", 0, 0, 1280, 768, 1)));
}

PauseState::~PauseState()
{
	delete background;
	delete font;
	TextureManager::getInstance()->clearFromTexture("pause_game_font");
}

void PauseState::processData()
{
	background->updateBackground();
	font->processData();
	if (!mObjects.empty())
	{
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->processData();
		}
	}
}
void PauseState::renderState()
{
	background->drawBackground();
	font->renderObject();
	if (mObjects.empty() == false)
	{
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->renderObject();
		}
	}
	StatusManager::getInstance()->renderOnGamePause();
}

bool PauseState::startState()
{
	ObjectParser::getInstance()->parserButton("pause_state.xml", mButton, mTexture);
	for (const auto& ite : mTexture)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}
	for (const auto& ite : mButton)
	{
		ButtonModel* obj = new ButtonModel();
		obj->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader(ite.textureID, ite.x, ite.y, ite.w, ite.h, ite.numFrames, ite.callbackID)));
		obj->setCallback(mCallback[ite.callbackID]);
		mObjects.push_back(obj);
	}


	return true;
}
bool PauseState::exitState()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->clearObject();
		delete mObjects[i];
	}
	for (size_t i = 0; i < mTexture.size(); ++i)
	{
		TextureManager::getInstance()->clearFromTexture(mTexture[i].textureID);
	}
	mTextureID.clear();
	mObjects.clear();
	return true;
}

void PauseState::m_sPauseToPlay()
{
	GameManager::getInstance()->getFSM()->popState();
}

void PauseState::m_sPauseToHome()
{
	GameManager::getInstance()->getFSM()->changeState(new HomeState());
}