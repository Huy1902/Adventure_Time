#include "EnemyObject.h"
#include "GameManager.h"
#include "InputManager.h"

EnemyObject::EnemyObject() :
	ObjectModel()
{

}

EnemyObject::~EnemyObject()
{

}

void EnemyObject::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ObjectModel::loadTexture(std::move(Info));
}

void EnemyObject::processData()
{
	//InputManager::getInstance()->takeInput();
	//if (InputManager::getInstance()->keyDown(SDL_SCANCODE_W))
	//{
	//	mPosition.setY(mPosition.getY() - 10);
	//}
	//if (InputManager::getInstance()->keyDown(SDL_SCANCODE_S))
	//{
	//	mPosition.setY(mPosition.getY() + 10);
	//}
	//if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A))
	//{
	//	mPosition.setX(mPosition.getX() - 10);
	//}
	//if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D))
	//{
	//	mPosition.setX(mPosition.getX() + 10);
	//}
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
}

void EnemyObject::renderObject() const
{
	ObjectModel::renderObject();
}

void EnemyObject::clearObject()
{

}
