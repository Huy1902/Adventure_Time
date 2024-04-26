#include "BaseModel.h"


BaseModel::BaseModel() :
	BaseObject()
{
	mPosition = new GameVector();
}

BaseModel::~BaseModel()
{
	delete mPosition;
}

void BaseModel::processData()
{
}

void BaseModel::renderObject() const
{
}

void BaseModel::clearObject()
{

}
