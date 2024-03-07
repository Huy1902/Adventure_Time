#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL.h>


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


private:
	static GameManager* s_pInstance;
	bool m_bRunning;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;

	SDL_Rect srcRect;
	SDL_Rect destRect;

	int mWidthWindows;
	int mHeightWindows;

	int mIndexFrame;

	GameManager();
	~GameManager();
};

#endif	// GAMEMANAGER_H_

