#include "ActionModel.h"

#include "BaseObject.h"

#include "TextureManager.h"
#include "GameManager.h"


ActionModel::ActionModel() :
	mCallback(nullptr),
	m_bRight(false),
	mIndexFrames(0),
	mNumFrames(0),
	mWidth(100),
	mHeight(64),
	mPosition(nullptr)
{
}
ActionModel::~ActionModel()
{

}

void ActionModel::processData()
{

}
void ActionModel::renderAction()
{

}
bool ActionModel::onEnter()
{

}
bool ActionModel::onExit()
{

}