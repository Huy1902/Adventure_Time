
#include <string>

#include "GameManager.h"


using namespace std;

const int FPS = 24;
const int DELAY_TIME = static_cast<int>( 1000.0f / FPS );

int main(int argc, char* args[])
{
	int begin_frame, time_frame;
	GameManager::getInstance()->initGame("Adventure Time", 300, 300, 1280, 768);

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