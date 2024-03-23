#ifndef ANIMATION_H_
#define ANIMATION_H_


#include "GameVector.h"
#include  <SDL.h>
class Animation
{
public:
	void update();
	void draw();
	void changeAnim(const std::string& textureID, const int& numFrame, SDL_RendererFlip flip);
	void changeAnim(const std::string& textureID, const int& numFrame, SDL_RendererFlip flip, const int& w, const int&h, const int & speed);

	void setPosition(const GameVector& position)
	{
		mPosition = position;
	}
	void setSize(int w, int h)
	{
		mW = w;
		mH = h;
	}
	void setSpeed(int v)
	{
		mSpeed = v;
	}
	int getWidth() const
	{
		return mW;
	}
	int getHeight() const
	{
		return mH;
	}
	/*static Animation* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Animation();
		}
		return s_pInstance;
	}*/
	Animation();
private:
	//static Animation* s_pInstance;

	int mIndexFrame;
	std::string mTextureID;
	int mNumFrame;
	SDL_RendererFlip mFlip;

	int mSpeed;

	int mW;
	int mH;
	GameVector mPosition;
};
#endif
