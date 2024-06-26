#ifndef STATUSMANAGER_H_
#define STATUSMANAGER_H_

#include "PlayerObject.h"
#include "EnemyObject.h"
#include "SpellObject.h"

#include "Animation.h"

class StatusManager
{
public:
	void updatePlayerStatus();
	void renderPlayerStatus();
	void setPlayer(PlayerObject* obj);

	bool whenPlayerAttackEnemy(EnemyObject* obj);
	bool whenEnemyAttackPlayer(EnemyObject* obj);
	bool whenSpellAttackEnemy(SpellObject* spell, EnemyObject* obj);
	void renderOnGamePause();

	void renderEnemyStatus(EnemyObject* obj);

	void renderBossStatus(EnemyObject * mBoss);

	static StatusManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new StatusManager();
		}
		return s_pInstance;
	}
	void setScore(int score)
	{
		mScore = score;
	}
	int getScore() const
	{
		return mScore;
	}
private:
	static StatusManager* s_pInstance;
	int HP;
	PlayerObject* mPlayer;

	Animation* avatar;

	StatusManager();
	~StatusManager();

	double getDMGtaken(const int& luck, const int& atk, const int& def);

	std::vector<Texture> mTextures;
	std::map<std::string, Bar> mBars;

	int mScore = 0;
};

#endif //STATUSMANAGER_H_

