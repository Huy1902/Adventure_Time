#include "HomeState.h"

#include "GameManager.h"
#include "ObjectModel.h"
#include "TextureManager.h"
#include "ButtonModel.h"
#include "LoadingState.h"

#include "ObjectParser.h"

#include "SoundManager.h"
#include "Cursor.h"


const std::string  HomeState::m_sHomeID = "HOME";

void HomeState::m_sHomeToPlay()
{
	SoundManager::getInstance()->playSound("play_button", 0, -1);
	GameManager::getInstance()->getFSM()->changeState(new LoadingState());
}

void HomeState::m_sExitHome()
{
	GameManager::getInstance()->quitGame();
}

void HomeState::m_sHomeToScore()
{
	std::cout << "enter Score\n";
}

HomeState::HomeState()
{
	mCallback.push_back(m_sHomeToPlay);
	mCallback.push_back(m_sHomeToScore);
	mCallback.push_back(m_sExitHome);

	background = new Background();
	TextureManager::getInstance()->load("assets/button/menu_font.png", "font", GameManager::getInstance()->getRenderer());
	font = new ObjectModel();
	font->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("font", 0, 0, 1280, 768, 1)));
}

HomeState::~HomeState()
{
	TextureManager::getInstance()->clearFromTexture("font");
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
		obj->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader(ite.textureID, ite.x, ite.y, ite.w, ite.h, ite.numFrames, ite.callbackID)));
		obj->setCallback(mCallback[ite.callbackID]);
		mObjects.push_back(obj);
	}


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
	delete font;
	delete background;
	return true;
}