//file header
#include "GameManager.h"

//file C lib
#include <Windows.h>

//file C++ lib
#include <iostream>

//file SDL2
#include <SDL_image.h>

using namespace std;

GameManager::GameManager() :
	m_bRunning(false),
	m_pWindow(nullptr),
	m_pRenderer(nullptr),
	m_pTexture(nullptr),
	mHeightWindows(0),
	mWidthWindows(0),
	srcRect({0, 0, 0, 0}),
	destRect({ 0, 0, 0, 0 })
{

}

GameManager::~GameManager()
{
}

void GameManager::InitGame(const char* t, int x, int y, int w, int h)
{
	//alloc console and write on it
	AllocConsole();
	cout << "alloc console...\n";
	FILE* consoleOutput;
	if (freopen_s(&consoleOutput, "CON", "w", stdout) != 0)
	{
		perror("freopents failed");
	}
	else
	{
	}

	mWidthWindows = w;
	mHeightWindows = h;

	//init SDL
	cout << "Init SDL...\n";
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Create window...\n";
		m_pWindow = SDL_CreateWindow(t, x, y, w, h, NULL);

		if (m_pWindow == NULL)
		{
			cout << "failed";
		}
		else
		{
			cout << "Create Renderer\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer == 0)
			{
				cout << "failed";
			}
			else
			{
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
		}
	}
	else
	{
		cout << "failed";
	}

	cout << "Create surface...\n";
	SDL_Surface* pSurface = IMG_Load("assets/main_character/vagabond_attack_Sheet.png");

	if (pSurface == NULL)
	{
		cout << "failed";
	}
	else
	{
		cout << "Create texture...\n";
		m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);

		SDL_FreeSurface(pSurface);
	}

	SDL_QueryTexture(m_pTexture, NULL, NULL, &srcRect.w, &srcRect.h);

	srcRect.w /= 15;


	destRect.x = 0;
	destRect.y = 0;
	destRect.w = srcRect.w * 3;
	destRect.h = srcRect.h * 3;

	m_bRunning = true;
}

void GameManager::TakeInput()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;

		default:
			break;
		}
	}
}

void GameManager::ProcessData()
{
	static int i = 0;
	srcRect.x = 128 * i;
	++i;
	if (i == 15)
	{
		i = 0;
	}
}

void GameManager::RenderWindows()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color
	SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &destRect);
	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void GameManager::CleanGame()
{
	std::cout << "cleaning game...\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}