#ifndef STATUSMANAGER_H_
#define STATUSMANAGER_H_

#include "PlayerObject.h"
#include "EnemyObject.h"

#include "Animation.h"

struct Bar
{
	int x;
	int y;
	int w;
	int h;
};

class StatusManager
{
public:
	void updatePlayerStatus();
	void renderPlayerStatus();
	void setPlayer(PlayerObject* obj);

	bool whenPlayerAttackEnemy(EnemyObject* obj);
	bool whenEnemyAttackPlayer(EnemyObject* obj);

	void renderOnGamePause();

	static StatusManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new StatusManager();
		}
		return s_pInstance;
	}
private:
	static StatusManager* s_pInstance;
	int HP;
	PlayerObject* mPlayer;

	SDL_Rect mSrcPoint;
	SDL_Rect mDestPoint;
	SDL_Rect mSrcHealth;
	SDL_Rect mDestHealth;
	Status mCurrentPlayer;
	Status mMaxPlayer;

	Animation* avatar;

	int mDecreasePoint;
	int mLenPoint;

	StatusManager();
	~StatusManager();

	double getDMGtaken(const int& luck, const int& atk, const int& def);

	std::vector<Texture> mTexture;
};

#endif //STATUSMANAGER_H_

