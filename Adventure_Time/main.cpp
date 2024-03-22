
#include <string>

#include "GameManager.h"


using namespace std;

const int FPS = 24;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
	int begin_frame, time_frame;
	GameManager::getInstance()->initGame("Test", 300, 300, 1280, 768);

	//fout << layerstring;
	//Map* new_map = new Map();
	//new_map->loadMap("map1.txt", "tileset1");
	//while (1)
	//{
	//	SDL_RenderClear(GameManager::getInstance()->getRenderer()); // clear the renderer to the draw color
	//	new_map->updateMap();
	//	new_map->renderMap();

	//	SDL_RenderPresent(GameManager::getInstance()->getRenderer()); // draw to the screen
	//	SDL_Delay(10);
	//}


	//system("pause");


	while (GameManager::getInstance()->getRunning() == true)
	{
		begin_frame = SDL_GetTicks();

		GameManager::getInstance()->takeInput();
		GameManager::getInstance()->processData();
		GameManager::getInstance()->renderWindows();

		time_frame = SDL_GetTicks() - begin_frame;
		if (time_frame < DELAY_TIME)
		{
			SDL_Delay((int)(DELAY_TIME - time_frame));
		}
	}

	GameManager::getInstance()->clearGame();
	return 0;
}