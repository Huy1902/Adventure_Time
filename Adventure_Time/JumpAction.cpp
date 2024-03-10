#include "JumpAction.h"
#include "GameManager.h"

JumpAction::JumpAction() :
	ActionModel()
{

}

JumpAction::~JumpAction()
{

}

void JumpAction::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ActionModel::loadTexture(std::move(Info));
}

void JumpAction::processData()
{
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
}

void JumpAction::renderObject() const
{
	ActionModel::renderObject();
}

void JumpAction::clearObject()
{

}
