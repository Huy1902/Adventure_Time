#include "ScoreState.h"

#include "GameManager.h"
#include "ObjectModel.h"
#include "TextureManager.h"
#include "ButtonModel.h"
#include "ObjectParser.h"
#include "HomeState.h"
#include "Cursor.h"
#include "StandingManager.h"
#include "FontManager.h"

using namespace std;
const string ScoreState::m_sScoreID = "Score";



ScoreState::ScoreState()
{
	mCallback.push_back(m_sScoreToHome);

	background = new Background();
	TextureManager::getInstance()->load("assets/button/score_font.png", "score_font", GameManager::getInstance()->getRenderer());
	font = new ObjectModel();
	font->loadTexture(unique_ptr<TextureLoader>(new TextureLoader("score_font", 0, 0, 1280, 768, 1)));
}

ScoreState::~ScoreState()
{
	mCallback.clear();
	delete background;
	delete font;
	TextureManager::getInstance()->clearFromTexture("score_font");
}

void ScoreState::processData()
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
void ScoreState::renderState()
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
	for (int i = 0; i < mStanding.size(); ++i)
	{
		FontManager::getInstance()->drawText(to_string(mStanding[i]).c_str(), 630, 280 + i * 160, 48);
	}
	Cursor::getInstance()->render();
}

bool ScoreState::startState()
{
	ObjectParser::getInstance()->parserButton("score_state.xml", mButton, mTexture);
	for (const auto& ite : mTexture)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}
	for (const auto& ite : mButton)
	{
		ButtonModel* obj = new ButtonModel();
		obj->loadTexture(unique_ptr<TextureLoader>(new TextureLoader(ite.textureID, ite.x, ite.y, ite.w, ite.h, ite.numFrames, ite.callbackID)));
		obj->setCallback(mCallback[ite.callbackID]);
		mObjects.push_back(obj);
	}
	StandingManager::getInstance()->updateScoreStanding();
	mStanding = StandingManager::getInstance()->getStanding();
	return true;
}
bool ScoreState::exitState()
{
	for (size_t i = 0; i < mObjects.size(); ++i)
	{
		mObjects[i]->clearObject();
		delete mObjects[i];
	}
	mObjects.clear();
	for (size_t i = 0; i < mTexture.size(); ++i)
	{
		TextureManager::getInstance()->clearFromTexture(mTexture[i].textureID);
	}
	mTextureID.clear();
	mButton.clear();
	mStanding.clear();
	return true;
}

void ScoreState::m_sScoreToHome()
{
	GameManager::getInstance()->getFSM()->changeState(new HomeState());
}
