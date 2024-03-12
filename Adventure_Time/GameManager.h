#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

//file C++
#include <vector>

//SDL2 file
#include <SDL.h>

//project file
#include "BaseObject.h"

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
	void quitGame();
	void clearGame();

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

	int getWidthWindows() const { return mWidthWindows; }
	int getHeightWindows() const { return mHeightWindows; }

private:
	static GameManager* s_pInstance;
	bool m_bRunning;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;

	int mWidthWindows;
	int mHeightWindows;

	std::vector<BaseObject*> mBaseObject;

	GameManager();
	~GameManager();
};

#endif	// GAMEMANAGER_H_

