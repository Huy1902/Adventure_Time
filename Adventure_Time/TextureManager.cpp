#include "TextureManager.h"

//file SDL
#include "SDL_image.h"

#include <iostream>

using namespace std;

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{

}

void TextureManager::load(const std::string& fileName, const std::string& id, SDL_Renderer* pRenderer)
{
	cout << "Load surface...\n";
	SDL_Surface* pSurface = IMG_Load(fileName.c_str());
	if (pSurface == 0)
	{
		cout << "failed";
	}
	else
	{
		cout << "Create texture...\n";
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
		if (pTexture == 0)
		{
			cout << "failed";
		}
		else
		{
			mTexture[id] = pTexture;
		}
		SDL_FreeSurface(pSurface);
	}
	
}

void TextureManager::drawSpritePic(const std::string& id, int x, int y,
	int w, int h, double a , int indexFrame,
	SDL_Point* c, SDL_RendererFlip f, SDL_Renderer* pRenderer)
{
	SDL_Rect srcRect = { w * indexFrame, 0, w, h };
	SDL_Rect destRect = { x, y, w, h };

	SDL_RenderCopyEx(pRenderer, mTexture[id], &srcRect, &destRect, a, c, f);
}
