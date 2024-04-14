#include "Tips.h"

#include <fstream> 
#include <iostream> 
#include <random>

#include "FontManager.h"
#include "TextureManager.h"
#include "GameManager.h"
using namespace std;

const int NUMBER_OF_TIP = 2;
const string PATH = "assets/tips/";
const string NAME = "tip";
void Tips::loadTip()
{
	int id = rand() % NUMBER_OF_TIP;
	string temp = PATH + NAME + to_string(id) + ".txt";
	ifstream fin;
	fin.open(temp);
	getline(fin, mTip);
	cout << mTip << '\n';
	fin.close();

	temp = PATH + NAME + to_string(id) + ".png";
	TextureManager::getInstance()->load(temp, "tip", GameManager::getInstance()->getRenderer());
}

void Tips::exitTip()
{
	TextureManager::getInstance()->clearFromTexture("tip");
}

void Tips::renderTip(int x, int y)
{
	FontManager::getInstance()->drawText(mTip.c_str(), x, y);
	TextureManager::getInstance()->drawSinglePic("tip", x - 30, y, 25, 25, GameManager::getInstance()->getRenderer());
}
Tips* Tips::s_pInstance = nullptr;

Tips::Tips()
{
	srand(static_cast<unsigned int>(time(NULL)));
}
