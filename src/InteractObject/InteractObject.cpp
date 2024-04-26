#include "InteractObject.h"

#include "TextureManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "FontManager.h"

InteractObject::InteractObject()
{
	//mPosition = new GameVector();
	//mMapPosition = new GameVector();

	//mTextureID = "bonfire";
	//mHeight = 60;
	//mWidth = 40;
	//mNumFrames = 9;

	mType = NOTHING;
}


bool InteractObject::interactItem()
{
	//m_bAbleToInteract = true;
	//if (InputManager::getInstance()->keyDown(SDL_SCANCODE_F))
	//{
	//	return true;
	//}
	return false;
}

InteractObject::~InteractObject()
{
	delete mMapPosition;
}

void InteractObject::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	mTextureID = Info->getTextureID();
	mPosition = new GameVector(Info->getX(), Info->getY());
	mHeight = Info->getHeight();
	mWidth = Info->getWidth();
	mNumFrames = Info->getNumFrames();
}

void InteractObject::processData()
{
	//++mIndexFrames;
	//if (mIndexFrames == mNumFrames)
	//{
	//	mIndexFrames = 0;
	//}
	//m_bAbleToInteract = false;
}

void InteractObject::renderObject() const
{
	//int x = static_cast<int>(mPosition->getX() - mMapPosition->getX());
	//int y = static_cast<int>(mPosition->getY() - mMapPosition->getY());

	//TextureManager::getInstance()->drawSpritePicByCol(mTextureID, x, y,
	//	mWidth, mHeight, GameManager::getInstance()->getRenderer(), mIndexFrames, SDL_FLIP_NONE);
}

void InteractObject::clearObject()
{

}