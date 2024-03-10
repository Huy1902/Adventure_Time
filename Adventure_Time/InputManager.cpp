#include "InputManager.h"
#include "GameManager.h"

InputManager* InputManager::s_pInstance = nullptr;

InputManager::InputManager(): mKeyButton(nullptr)
{
	mMousePosition = new GameVector();
	mMouseButton.resize(3, false);
}

InputManager::~InputManager()
{

}

void InputManager::takeInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			isKeyDown();
			break;
		case SDL_KEYUP:
			isKeyUp();
			break;
		case SDL_MOUSEMOTION:
			isMouseMove(event);
			break;
		case SDL_MOUSEBUTTONUP:
			isMouseUp(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			isMouseDown(event);
			break;
		case SDL_QUIT:
			GameManager::getInstance()->quitGame();
			break;
		default:
			break;
		}
	}
}

void InputManager::isKeyDown()
{
	mKeyButton = SDL_GetKeyboardState(0);
}
void InputManager::isKeyUp()
{
	mKeyButton = SDL_GetKeyboardState(0);
}
bool InputManager::keyDown(SDL_Scancode key)
{
	if (mKeyButton != NULL)
	{
		if (mKeyButton[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void InputManager::isMouseMove(SDL_Event& event)
{
	*mMousePosition = std::make_pair(event.motion.x, event.motion.y);
}
void InputManager::isMouseDown(SDL_Event& event)
{
	switch (event.button.button)
	{
	case SDL_BUTTON_LEFT:
		mMouseButton[LEFT] = true;
		break;
	case SDL_BUTTON_MIDDLE:
		mMouseButton[MIDDLE] = true;
		break;
	case SDL_BUTTON_RIGHT:
		mMouseButton[RIGHT] = true;
		break;
	}
}
void InputManager::isMouseUp(SDL_Event& event)
{
	switch (event.button.button)
	{
	case SDL_BUTTON_LEFT:
		mMouseButton[LEFT] = false;
		break;
	case SDL_BUTTON_MIDDLE:
		mMouseButton[MIDDLE] = false;
		break;
	case SDL_BUTTON_RIGHT:
		mMouseButton[RIGHT] = false;
		break;
	}
}

void InputManager::clearInput()
{

}
