#include "HomeState.h"

#include <fstream>

#include "GameManager.h"
#include "ObjectModel.h"
#include "TextureManager.h"
#include "ButtonModel.h"
#include "LoadingState.h"
#include "ScoreState.h"

#include "ObjectParser.h"

#include "SoundManager.h"
#include "StatusManager.h"
#include "Cursor.h"

#include "StandingManager.h"

using namespace std;
const string  HomeState::m_sHomeID = "HOME";

void HomeState::m_sHomeToPlay()
{
	SoundManager::getInstance()->playSound("play_button", 0, -1);
	GameManager::getInstance()->getFSM()->changeState(new LoadingState());
}

void HomeState::m_sExitHome()
{
	StandingManager::getInstance()->resetStanding();
	GameManager::getInstance()->quitGame();
}

void HomeState::m_sHomeToScore()
{
	GameManager::getInstance()->getFSM()->changeState(new ScoreState());
}

void HomeState::m_sMusicControl()
{
	if (SoundManager::getInstance()->isMutedMusic() == true)
	{
		SoundManager::getInstance()->enableMusic();
	}
	else
	{
		SoundManager::getInstance()->muteMusic();
	}
}

void HomeState::m_sSFXControl()
{
	if (SoundManager::getInstance()->isMutedSFX() == true)
	{
		SoundManager::getInstance()->enableSFX();
	}
	else
	{
		SoundManager::getInstance()->muteSFX();
	}
}

HomeState::HomeState()
{
	mCallback.push_back(m_sHomeToPlay);
	mCallback.push_back(m_sHomeToScore);
	mCallback.push_back(m_sExitHome);
	mCallback.push_back(m_sMusicControl);
	mCallback.push_back(m_sSFXControl);

	background = new Background();
	font = new ObjectModel();
}

HomeState::~HomeState()
{
	delete font;
	delete background;
}

void HomeState::processData()
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
void HomeState::renderState()
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
	Cursor::getInstance()->render();
}

bool HomeState::startState()
{
	/*TextureManager::getInstance()->load("assets/play_button.png", "play_button", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/exit_button.png", "exit_button", GameManager::getInstance()->getRenderer());*/
	ObjectParser::getInstance()->parserButton("home_state.xml", mButton, mTexture);
	for (const auto& ite : mTexture)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}
	for (const auto& ite : mButton)
	{
		ButtonModel* obj = new ButtonModel();
		obj->loadTexture(unique_ptr<TextureLoader>(new TextureLoader(ite.textureID, ite.x, ite.y, ite.w, ite.h, ite.numFrames, ite.callbackID)));
		if (ite.callbackID >= 3)
		{
			obj->setSwift();
			obj->setCallback(mCallback[ite.callbackID]);
			if (ite.callbackID == 3)
			{
				obj->setIndexFrame(SoundManager::getInstance()->isMutedMusic());//music
			}
			else
			{
				obj->setIndexFrame(SoundManager::getInstance()->isMutedSFX());
			}
		}
		else
		{
			obj->setCallback(mCallback[ite.callbackID]);
		}
		mObjects.push_back(obj);
	}
	font->loadTexture(unique_ptr<TextureLoader>(new TextureLoader("font", 0, 0, 1280, 768, 1)));
	return true;
}
bool HomeState::exitState()
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
	mButton.clear();

	ofstream fout("score_buffer.txt");

	fout << StatusManager::getInstance()->getScore() << '\n';

	fout.close();
	delete font;
	delete background;
	return true;
}