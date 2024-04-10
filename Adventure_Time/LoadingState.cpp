#include "LoadingState.h"

#include "ObjectModel.h"
#include "TextureManager.h"
#include "PlayingState.h"

#include "PlayingState.h"
#include "GameManager.h"

const std::string LoadingState::m_sGameLoading = "GAME_LOADING";



LoadingState::LoadingState()
{
	TextureManager::getInstance()->load("assets/background4.png", "background4", GameManager::getInstance()->getRenderer());
	//TextureManager::getInstance()->load("assets/button/game_over_font.png", "game_over_font", GameManager::getInstance()->getRenderer());
	//font = new ObjectModel();
	//font->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("game_over_font", 0, 0, 1280, 768, 1)));
}

LoadingState::~LoadingState()
{
	//TextureManager::getInstance()->clearFromTexture("game_over_font");
}

void LoadingState::processData()
{
	--mCountToPlay;
	if (mCountToPlay == 0)
	{
		GameManager::getInstance()->getFSM()->changeState(new PlayingState());
	}
}
void LoadingState::renderState()
{
	TextureManager::getInstance()->drawSinglePic("background4", 0, 0, 1280, 768, GameManager::getInstance()->getRenderer());
}

bool LoadingState::startState()
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
	return true;
}
bool LoadingState::exitState()
{
	//for (size_t i = 0; i < mObjects.size(); ++i)
	//{
	//	mObjects[i]->clearObject();
	//	delete mObjects[i];
	//}
	//for (size_t i = 0; i < mTexture.size(); ++i)
	//{
	//	TextureManager::getInstance()->clearFromTexture(mTexture[i].textureID);
	//}
	//mTextureID.clear();
	//mObjects.clear();

	return true;
}
