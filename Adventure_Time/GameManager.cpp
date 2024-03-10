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
#include "TextureLoader.h"
#include "EnemyObject.h"
#include "PlayerObject.h"
using namespace std;

GameManager* GameManager::s_pInstance = nullptr;

GameManager::GameManager() :
	m_bRunning(false),
	m_pWindow(nullptr),
	m_pRenderer(nullptr),
	m_pTexture(nullptr),
	mHeightWindows(0),
	mWidthWindows(0)
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
	TextureManager::getInstance()->load("assets/main_character/vagabond_run_Sheet.png", "run", m_pRenderer);
	TextureManager::getInstance()->load("assets/main_character/vagabond_jump_Sheet.png", "jump", m_pRenderer);
	TextureManager::getInstance()->load("assets/main_character/vagabond.png", "vagabond", m_pRenderer);

	EnemyObject* enemy = new EnemyObject();
	PlayerObject* player = new PlayerObject();
	player->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("vagabond", 0, 0, 64, 64, 1, 2.5) ));
	mGameObject.push_back(player);
	enemy->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("vagabond", 0, 0, 64, 64, 1, 2.5)));
	mGameObject.push_back(enemy);

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
	for (GameObject* obj : mGameObject)
	{
		obj->processData();
	}
}

void GameManager::renderWindows()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color

	for (GameObject* obj : mGameObject)
	{
		obj->renderObject();
	}

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void GameManager::quitGame()
{
	m_bRunning = false;
}

void GameManager::clearGame()
{
	std::cout << "clearing game...\n";
	for (GameObject* obj : mGameObject)
	{
		obj->clearObject();
	}
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}