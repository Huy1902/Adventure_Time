#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL.h>

#include "GameObject.h"

class GameManager
{
public:
	// Init windows for game with:
	//t : title
	//x, y : position
	//w, h : size
	void initGame(const char* t, int x, int y, int w, int h);
	void takeInput();
	void processData();
	void renderWindows();
	void cleanGame();

	static GameManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new GameManager();
		}
		return s_pInstance;
	}

	void setRunning(bool running) { m_bRunning = running; }
	bool getRunning() const { return m_bRunning; }

	SDL_Renderer* getRenderer() const { return m_pRenderer; }

private:
	static GameManager* s_pInstance;
	bool m_bRunning;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;

	int mWidthWindows;
	int mHeightWindows;

	GameObject* player;

	GameManager();
	~GameManager();
};

#endif	// GAMEMANAGER_H_

