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
	void InitGame(const char* t, int x, int y, int w, int h);
	void TakeInput();
	void ProcessData();
	void RenderWindows();
	void CleanGame();

	static GameManager* getInstance()
	{
		static GameManager* pInstance = new GameManager();
		return pInstance;
	}
	
	void setRunning(bool running) { m_bRunning = running; }
	bool getRunning() const { return m_bRunning; }


private:
	bool m_bRunning;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pTexture;

	SDL_Rect srcRect;
	SDL_Rect destRect;

	int mWidthWindows;
	int mHeightWindows;

	GameManager();
	~GameManager();
};

#endif	// GAMEMANAGER_H_

