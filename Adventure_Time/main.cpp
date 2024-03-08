#include "GameManager.h"

using namespace std;

int main(int argc, char* args[])
{
	GameManager::getInstance()->initGame("Test", 100, 100, 1280, 720);

	while (GameManager::getInstance()->getRunning() == true)
	{
		GameManager::getInstance()->takeInput();
		GameManager::getInstance()->processData();
		GameManager::getInstance()->renderWindows();

		SDL_Delay(100);
	}

	GameManager::getInstance()->clearGame();
	return 0;
}