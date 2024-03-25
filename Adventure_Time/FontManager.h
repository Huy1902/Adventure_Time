#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>
class FontManager
{
public:
	static FontManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new FontManager();
		}
		return s_pInstance;
	}

	//load image from pathfileName to pRenderer with id
	void loadText(const std::string& fileName, int size, SDL_Renderer* pRenderer);


	void drawText(const char* text, int x, int y);
private:
	static FontManager* s_pInstance;

	SDL_Color mColor;
	TTF_Font* mFont;
	SDL_Renderer* mRenderer;

	FontManager();
	~FontManager();
};

