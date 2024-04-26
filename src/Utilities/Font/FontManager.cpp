#include "FontManager.h"

#include <iostream>

#include "GameManager.h"
using namespace std;

FontManager* FontManager::s_pInstance = nullptr;

FontManager::FontManager()
{
	TTF_Init();
	mColor = { 255, 255, 255 };
	mRenderer = nullptr;
}

FontManager::~FontManager()
{
	TTF_Quit();
}

void FontManager::loadText(const std::string& fileName, int size, SDL_Renderer* pRenderer)
{
	cout << "Load font...\n";
	TTF_Font* mFont = TTF_OpenFont(fileName.c_str(), size);

	mRenderer = pRenderer;
	mColor = { 255, 255, 255 };
	mFontMap[size] = mFont;
}

void FontManager::drawText(const char*text, int x, int y, int size)
{
	SDL_Surface* surface = TTF_RenderText_Solid(mFontMap[size], text, mColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);

	SDL_Rect messageRect = { x, y, 0, 0 };
	TTF_SizeText(mFontMap[size], text, &messageRect.w, &messageRect.h);
	SDL_RenderCopy(mRenderer, texture, NULL, &messageRect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
