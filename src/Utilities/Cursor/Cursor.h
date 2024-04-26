#ifndef CURSOR_H_
#define CURSOR_H

#include "GameVector.h"
#include "Animation.h"
class Cursor
{
public:
	void render();
	void renderLoading();
	static Cursor* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Cursor();
		}
		return s_pInstance;
	}
private:
	static Cursor* s_pInstance;
	Animation mAnimation;
	Cursor();
	~Cursor();
};

#endif //CURSOR_H

