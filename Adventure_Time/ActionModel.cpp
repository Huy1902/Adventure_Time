#include "ActionModel.h"

#include "GameObject.h"

#include "TextureManager.h"
#include "GameManager.h"

ActionModel::ActionModel(const std::string textureID, int w, int h, int numFrames, float scope) :
	GameObject(),
	mTextureID(""),
	mIndexFrames(0),
	mSize({ w, h }),
	mNumFrames(numFrames),
	mScope(scope)
{

}

ActionModel::~ActionModel()
{

}

void ActionModel::processData()
{
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
}

void ActionModel::renderObject() const
{
	int x = static_cast<int>(mPosition.getX());
	int y = static_cast<int>(mPosition.getY());

	TextureManager::getInstance()->drawSpritePic(mTextureID, x, y,
		mSize.getW(), mSize.getH(), GameManager::getInstance()->getRenderer(), mIndexFrames, mScope);
}

void ActionModel::clearObject()
{

}