#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

//file SDL2
#include "SDL.h"

//file C++ lib
#include <string>
#include <map>


class TextureManager
{
public:
	static TextureManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new TextureManager();
		}
		return s_pInstance;
	}

	//load image from pathfileName to pRenderer with id
	void load(const std::string& fileName, const std::string& id, SDL_Renderer* pRenderer);

	//draw image with attribute:
	//id: ID in Texture
	//x, y: position
	//w, h: size
	//c: { , } position on X,Y axis to rotate
	//a: angle to rotate
	//f: flag to flip
	void drawSpritePicByCol(const std::string& id, const int& x, const int& y,
		const int& w, const int& h, SDL_Renderer* pRenderer = nullptr, const int& indexFrame = 0,
		SDL_RendererFlip f = SDL_FLIP_NONE, double a = 0.0, SDL_Point* c = NULL);

	void drawSinglePic(const std::string& id, const int& x, const int& y, const int& w, const int& h, SDL_Renderer* pRenderer);

	void clearFromTexture(const std::string & id);

	SDL_Texture* getTexture(const std::string & id) { return mTexture[id]; }
private:
	static TextureManager* s_pInstance;

	std::map<std::string, SDL_Texture*> mTexture;

	TextureManager();
	~TextureManager();
};

#endif // TEXTUREMANAGER_H_

