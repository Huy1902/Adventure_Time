#ifndef SPELLMANAGER_H_
#define SPELLMANAGER_H_

#include <vector>
#include "GameVector.h"

#include "SpellObject.h"
#include "EnemyObject.h"

class SpellManager
{
public:
	static SpellManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new SpellManager();
		}
		return s_pInstance;
	}
	void addPlayerSpell(const std::string nameSpell, const GameVector& pos, bool isRight);
	/*const std::vector<SpellObject*> getEnemyArrow() { return mEnemyArrows; }*/
	bool checkCollisionWithPlayerSpell(EnemyObject* enemy);

	void setMapPosition(const GameVector& pos)
	{
		mMapPosition = pos;
	}
	void updateSpell();
	void renderSpell();
private:
	SpellManager();
	~SpellManager();
	static SpellManager* s_pInstance;
	std::vector<SpellObject*> mPlayerSpell;

	GameVector mMapPosition;
};

#endif //SPELLMANAGER_H_