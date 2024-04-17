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
	void addPlayerSpell(const std::string nameSpell, const GameVector& pos, const GameVector& mapPos, bool isRight);
	/*const std::vector<SpellObject*> getEnemyArrow() { return mEnemyArrows; }*/
	bool checkCollisionWithPlayerSpell(EnemyObject* player);

	void updateSpell();
	void renderSpell();
private:
	SpellManager();
	~SpellManager();
	static SpellManager* s_pInstance;
	std::vector<SpellObject*> mPlayerSpell;
};

#endif //SPELLMANAGER_H_