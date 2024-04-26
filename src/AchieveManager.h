#ifndef ACHIEVEMANAGER_H_
#define ACHIEVEMANAGER_H_

#include "Animation.h"
#include <map>
#include <vector>
#include <string>

enum Achieve_type
{
	NONE_ARCHIEVE = -1,
	BOSS_DESTROYED = 0,
	BONFIRE_LIT = 1,
	BONFIRE_REVIVAL = 2,
	MAIN_DEATH = 3,
	NEW_AREA = 4
};
struct Info;
struct Texture;

class AchieveManager
{
public:
	void takeAchieve(Achieve_type archive);
	void renderAchieve();
	void updateAchieve();
	static AchieveManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new AchieveManager();
		}
		return s_pInstance;
	}
private:
	static AchieveManager* s_pInstance;
	void startAchieve(const std::string& name);
	void loadTexture(int i);
	void clearTexture(int i);
	void endAchieve();
	Achieve_type mCurrentAchieve;
	Animation* mAnimation;
	std::map<std::string, Info> mAchieve;
	std::vector<Texture> mTexture;
	int mCountTimeAnimation;
	AchieveManager();
	~AchieveManager();
};

#endif // AchieveMANAGER_H_

