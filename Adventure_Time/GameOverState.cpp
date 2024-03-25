#include "GameOverState.h"

#include "GameManager.h"
#include "ObjectModel.h"
#include "TextureManager.h"
#include "ButtonModel.h"
#include "PlayingState.h"

#include "ObjectParser.h"

#include "SoundManager.h"

#include "HomeState.h"
#include "PlayingState.h"

const std::string  GameOverState::m_sGameOverID = "GAME_OVER";



GameOverState::GameOverState()
{
	mCallback.push_back(m_sGameOverToPlay);
	mCallback.push_back(m_sGameOverToHome);

	background = new Background();
	TextureManager::getInstance()->load("assets/button/game_over_font.png", "game_over_font", GameManager::getInstance()->getRenderer());
	font = new ObjectModel();
	font->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("game_over_font", 0, 0, 1280, 768, 1)));
}

GameOverState::~GameOverState()
{
	TextureManager::getInstance()->clearFromTexture("game_over_font");
}

void GameOverState::processData()
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
void GameOverState::renderState()
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

}

bool GameOverState::startState()
{
	ObjectParser::getInstance()->parserButton("game_over_state.xml", mButton, mTexture);
	for (const auto& ite : mTexture)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}
	for (const auto& ite : mButton)
	{
		ButtonModel* obj = new ButtonModel();
		obj->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader(ite.textureID, ite.x, ite.y, ite.w, ite.h, ite.numFrames, 1.0, ite.callbackID)));
		obj->setCallback(mCallback[ite.callbackID]);
		mObjects.push_back(obj);
	}


	return true;
}
bool GameOverState::exitState()
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

void GameOverState::m_sGameOverToPlay()
{
	GameManager::getInstance()->getFSM()->changeState(new PlayingState());
}

void GameOverState::m_sGameOverToHome()
{
	GameManager::getInstance()->getFSM()->changeState(new HomeState());
}
