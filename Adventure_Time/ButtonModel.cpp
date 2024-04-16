#include "ButtonModel.h"

#include "InputManager.h"

#include "SoundManager.h"
ButtonModel::ButtonModel() :
	ObjectModel(),
	m_bReleased(false),
	mCallback(nullptr)
{
	mIndexFrames = MOUSE_OUT;
}

ButtonModel::~ButtonModel()
{

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
		if (InputManager::getInstance()->getMouseButton(LEFT) && m_bReleased == true)
		{
			SoundManager::getInstance()->playSound("click_button", 0, -1);
			//mIndexFrames = CLICKED;
			mCallback();
			m_bReleased = false;
		}
		else
		{
			m_bReleased = true;
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


