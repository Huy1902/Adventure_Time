//file header
#include "GameManager.h"

//file C lib
#include <Windows.h>

//file C++ lib
#include <iostream>

//file SDL2
#include <SDL_image.h>


//project file
#include "TextureManager.h"
using namespace std;

GameManager* GameManager::s_pInstance = nullptr;

GameManager::GameManager() :
	m_bRunning(false),
	m_pWindow(nullptr),
	m_pRenderer(nullptr),
	m_pTexture(nullptr),
	mIndexFrame(0),
	mHeightWindows(0),
	mWidthWindows(0),
	srcRect({0, 0, 0, 0}),
	destRect({ 0, 0, 0, 0 })
{

}

GameManager::~GameManager()
{
}

void GameManager::initGame(const char* t, int x, int y, int w, int h)
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

	cout << "Load image...\n";
	TextureManager::getInstance()->load("assets/main_character/vagabond_attack_Sheet.png", "attack", m_pRenderer);
	m_bRunning = true;
}

void GameManager::takeInput()
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

void GameManager::processData()
{
	++mIndexFrame;
	if (mIndexFrame == 15)
	{
		mIndexFrame = 0;
	}
}

void GameManager::renderWindows()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color

	TextureManager::getInstance()->drawSpritePic("attack", 0, 0, 128, 64, m_pRenderer, mIndexFrame, 2.5);

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void GameManager::cleanGame()
{
	std::cout << "cleaning game...\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}