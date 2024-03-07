#include "GameManager.h"

using namespace std;

int main(int argc, char* args[])
{
	GameManager::getInstance()->InitGame("Test", 100, 100, 1280, 720);

	while (GameManager::getInstance()->getRunning() == true)
	{
		GameManager::getInstance()->TakeInput();
		GameManager::getInstance()->ProcessData();
		GameManager::getInstance()->RenderWindows();

		SDL_Delay(100);
	}

	GameManager::getInstance()->CleanGame();
	return 0;
}