#include "TextureManager.h"

//file SDL
#include "SDL_image.h"

#include <iostream>

using namespace std;

TextureManager* TextureManager::s_pInstance = nullptr;

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
	if (pSurface == NULL)
	{
		cout << "failed";
	}
	else
	{
		cout << "Create texture...\n";
		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
		if (pTexture == NULL)
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
	int w, int h, SDL_Renderer* pRenderer, int indexFrame, double scope,
	SDL_RendererFlip f, double a, SDL_Point* c)
{
	SDL_Rect srcRect = { w * indexFrame, 0, w, h };
	SDL_Rect destRect = { x, y, w * scope, h * scope };

	SDL_RenderCopyEx(pRenderer, mTexture[id], &srcRect, &destRect, a, c, f);
}
