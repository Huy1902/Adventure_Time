#include "Cursor.h"

#include "InputManager.h"
#include "TextureManager.h"
#include "GameManager.h"
Cursor* Cursor::s_pInstance = nullptr;

void Cursor::render()
{
	InputManager::getInstance()->takeCursor();
	GameVector* pos = InputManager::getInstance()->getMousePosition();
	TextureManager::getInstance()->drawSinglePic("cursor1", pos->getX(), pos->getY(), 29, 36, GameManager::getInstance()->getRenderer());
}

void Cursor::renderLoading()
{
	InputManager::getInstance()->takeCursor();
	GameVector* pos = InputManager::getInstance()->getMousePosition();
	mAnimation.setPosition(*pos);
	mAnimation.update();
	mAnimation.draw();
}

Cursor::Cursor()
{
	TextureManager::getInstance()->load("assets/cursor/cursor1.png", "cursor1", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/cursor/cursor2.png", "cursor2", GameManager::getInstance()->getRenderer());
	mAnimation.changeAnim("cursor2", 10, SDL_FLIP_NONE, 60, 60, 1);
}

Cursor::~Cursor()
{
	TextureManager::getInstance()->clearFromTexture("cursor1");
}
