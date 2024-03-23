#include "ButtonModel.h"

#include "InputManager.h"
ButtonModel::ButtonModel() :
	ObjectModel(),
	m_bReleased(false),
	mCallback(nullptr)
{
	mIndexFrames = MOUSE_OUT;
}

void ButtonModel::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	mCallbackID = Info->getCallbackID();
	ObjectModel::loadTexture(std::move(Info));
}

void ButtonModel::processData()
{ 
	GameVector* pMousePos = InputManager::getInstance()->getMousePosition();
	if (pMousePos->getX() <= mPosition->getX() + mWidth
		&& pMousePos->getX() >= mPosition->getX()
		&& pMousePos->getY() <= mPosition->getY() + mHeight
		&& pMousePos->getY() >= mPosition->getY()
		)
	{
		mIndexFrames = MOUSE_OVER;
		if (InputManager::getInstance()->getMouseButton(LEFT))
		{

			//mIndexFrames = CLICKED;
			mCallback();
			//m_bReleased = false;
		}
		else
		{
		}
	}
	else
	{
		mIndexFrames = MOUSE_OUT;
	}
}
void ButtonModel::renderObject() const
{
	ObjectModel::renderObject();
}
void ButtonModel::clearObject()
{
	ObjectModel::clearObject();
}