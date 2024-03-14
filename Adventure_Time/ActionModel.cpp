#include "ActionModel.h"

#include "BaseObject.h"

#include "TextureManager.h"
#include "GameManager.h"


ActionModel::ActionModel() :
	BaseObject(),
	m_bRight(false),
	m_bOnAir(false)
{
}
ActionModel::~ActionModel()
{

}

void ActionModel::processData()
{
	mTextureID = Info->getTextureID();
	mPosition = new GameVector(Info->getX(), Info->getY());
	mHeight = Info->getHeight();
	mWidth = Info->getWidth();
	mNumFrames = Info->getNumFrames();
	mScope = Info->getScope();
}
void ActionModel::renderAction()
{

}
bool ActionModel::onEnter()
{
	int x = static_cast<int>(mPosition->getX());
	int y = static_cast<int>(mPosition->getY());

	TextureManager::getInstance()->drawSpritePic(mTextureID, x, y,
		mWidth, mHeight, GameManager::getInstance()->getRenderer(), mIndexFrames, mScope);
}
bool ActionModel::onExit()
{

}