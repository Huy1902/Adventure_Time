#include "SDL2/include/SDL.h"
#include "SDL2//include/SDL_image.h"
#include <iostream>
#include <Windows.h>
using namespace std;

int main(int argc, char* args[])
{
	AllocConsole();
	FILE* consoleOutput;
	if (freopen_s(&consoleOutput, "CON", "w", stdout) != 0)
	{
		perror("freopen+s failed");
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		SDL_Window* pWindow = SDL_CreateWindow("Check", 300, 300, 640, 480, NULL);

		SDL_Renderer* pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

		SDL_Surface* pSurface = nullptr;
		pSurface =IMG_Load("assets/main_character/vagabond_attack_Sheet.png");
		if (pSurface == nullptr)
		{
			std::cout << "Error";
		}

		SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
		SDL_FreeSurface(pSurface);

		SDL_Rect srcRect = { 0, 0, 0, 0 };
		SDL_Rect destRect = { 0, 0, 0, 0 };

		SDL_QueryTexture(pTexture, NULL, NULL, &srcRect.w, &srcRect.h);
		srcRect.w /= 15;
		destRect.w = srcRect.w * 2;
		destRect.h = srcRect.h;
		destRect.h *= 2;
		destRect.x = srcRect.x = 0;
		destRect.y = srcRect.y = 0;
		

		SDL_RenderClear(pRenderer);

		SDL_RenderCopy(pRenderer, pTexture, &srcRect, &destRect);

		SDL_RenderPresent(pRenderer);


		SDL_Delay(3000);
		SDL_Quit();
	}
	return 0;
}