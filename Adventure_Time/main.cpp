#include "GameManager.h"
#include "Tileset.h"
#include "Layer.h"
#include <fstream>
#include <string>
using namespace std;

const int FPS = 24;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
	//fout << layerstring;
	int begin_frame, time_frame;
	GameManager::getInstance()->initGame("Test", 300, 300, 1280, 768);


	//ifstream fin;
	//ofstream fout("out.txt");
	//string layerstring = "";
	//string temp;
	//fin.open("maplayer1.txt");
	//while (fin >> temp)
	//{
	//	layerstring += temp;
	//}
	//Tileset* obj = new Tileset("assets/Tileset1.png", "tileset1", 32, 512, 512);
	//SDL_RenderClear(GameManager::getInstance()->getRenderer()); // clear the renderer to the draw color
	//Layer* layer1 = new Layer(layerstring, 24, 40, 32);
	//layer1->setTileset(obj);
	//layer1->renderLayer();

	//fin.close();
	//layerstring = "";
	//fin.open("maplayer2.txt");
	//fout << layerstring;
	//while (fin >> temp)
	//{
	//	layerstring += temp;
	//}
	//Layer* layer2 = new Layer(layerstring, 24, 40, 32);
	//layer2->setTileset(obj);
	//layer2->renderLayer();

	//fin.close();
	//layerstring = "";
	//fin.open("maplayer3.txt");
	//while (fin >> temp)
	//{
	//	layerstring += temp;
	//}
	//Layer* layer3 = new Layer(layerstring, 24, 40, 32);
	//layer3->setTileset(obj);
	//layer3->renderLayer();
	//SDL_RenderPresent(GameManager::getInstance()->getRenderer()); // draw to the screen

	//system("pause");


	//while (GameManager::getInstance()->getRunning() == true)
	//{
	//	begin_frame = SDL_GetTicks();

	//	GameManager::getInstance()->takeInput();
	//	GameManager::getInstance()->processData();
	//	GameManager::getInstance()->renderWindows();

	//	time_frame = SDL_GetTicks() - begin_frame;
	//	if (time_frame < DELAY_TIME)
	//	{
	//		SDL_Delay((int)(DELAY_TIME - time_frame));
	//	}
	//}

	GameManager::getInstance()->clearGame();
	return 0;
}