#include "LoadingState.h"

#include "ObjectModel.h"
#include "TextureManager.h"
#include "PlayingState.h"

#include "PlayingState.h"
#include "GameManager.h"
#include "Cursor.h"

const std::string LoadingState::m_sGameLoading = "GAME_LOADING";



LoadingState::LoadingState()
{
	TextureManager::getInstance()->load("assets/background4.png", "background4", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/loading.png", "loading_anime", GameManager::getInstance()->getRenderer());
	load = new Animation();
	load->changeAnim("loading_anime", 14, SDL_FLIP_NONE, 172, 64, 2);
	load->setPosition(GameVector{ 1100, 700 });
	mCountToPlay = 14 * 2;
}

LoadingState::~LoadingState()
{
	TextureManager::getInstance()->clearFromTexture("background4");
	TextureManager::getInstance()->clearFromTexture("loading_anime");
	delete load;
}

void LoadingState::processData()
{
	--mCountToPlay;
	load->update();
	if (mCountToPlay == 0)
	{
		GameManager::getInstance()->getFSM()->changeState(new PlayingState());
		
	}
}
void LoadingState::renderState()
{
	TextureManager::getInstance()->drawSinglePic("background4", 0, 0, 1280, 768, GameManager::getInstance()->getRenderer());
	load->draw();
	Cursor::getInstance()->renderLoading();
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
