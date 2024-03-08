#include "RunAction.h"
#include "GameManager.h"

RunAction::RunAction() :
	ActionModel()
{

}

RunAction::~RunAction()
{

}

void RunAction::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ActionModel::loadTexture(std::move(Info));
}

void RunAction::processData()
{
	mPosition.setX(mPosition.getX() + 10);
	mPosition.setY(mPosition.getY() + 10);
	if (mPosition.getX() == GameManager::getInstance()->getHeightWindows())
	{
		mPosition.setX(0);
		mPosition.setY(0);
	}
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
}

void RunAction::renderObject() const
{
	ActionModel::renderObject();
}

void RunAction::clearObject()
{

}
