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
#include "HomeState.h"
#include "InputManager.h"
#include "SoundManager.h"
using namespace std;

GameManager* GameManager::s_pInstance = nullptr;

GameManager::GameManager() :
	m_bRunning(false),
	m_pWindow(nullptr),
	m_pRenderer(nullptr),
	m_pTexture(nullptr),
	mHeightWindows(0),
	mWidthWindows(0),
	mFSM(nullptr)
{
	mTileSet.resize(1);
	mTileSet[0] = new TileInfo("assets/Tileset1.png", "tileset1", 32, 512, 512);
	mTileSet[0]->ground = { 65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,113 };

	SoundManager::getInstance()->loadSound("assets/music/Twilight_Serenity.mp3", "home_theme", MUSIC);
	SoundManager::getInstance()->loadSound("assets/music/Dream_Aria.mp3", "night_theme", MUSIC);
	SoundManager::getInstance()->loadSound("assets/music/Knights_of_Favonius.mp3", "play_theme", MUSIC);
	SoundManager::getInstance()->loadSound("assets/music/Make_Haste_Partner.mp3", "fight_theme", MUSIC);
	SoundManager::getInstance()->loadSound("assets/sfx/join_game.wav", "play_button", SFX);
	SoundManager::getInstance()->loadSound("assets/sfx/click_sfx.wav", "click_button", SFX);
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


	mFSM = new FiniteStateMachine();
	mFSM->pushState(new HomeState());

	m_bRunning = true;
}

void GameManager::takeInput()
{
	InputManager::getInstance()->takeInput();
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
	mFSM->processData();
}

void GameManager::renderWindows()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color

	mFSM->renderState();

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void GameManager::quitGame()
{
	m_bRunning = false;
}

void GameManager::clearGame()
{
	std::cout << "clearing game...\n";
	for (BaseObject* obj : mBaseObject)
	{
		obj->clearObject();
	}
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}