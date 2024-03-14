#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <vector>

#include <SDL.h>

#include "GameVector.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputManager
{
public:
	void takeInput();
	void clearInput();

	bool getMouseButton(int button) { return mMouseButton[button]; }
	GameVector* getMousePosition() const { return mMousePosition; }

	bool keyDown(SDL_Scancode key);

	static InputManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new InputManager();
		}
		return s_pInstance;
	}

	void resetState();
private:
	static InputManager* s_pInstance;

	std::vector<bool> mMouseButton;
	GameVector* mMousePosition;
	const Uint8* mKeyButton;

	void isKeyDown();
	void isKeyUp();

	void isMouseMove(SDL_Event& event);
	void isMouseDown(SDL_Event& event);
	void isMouseUp(SDL_Event& event);

	InputManager();
	~InputManager();
};

#endif

