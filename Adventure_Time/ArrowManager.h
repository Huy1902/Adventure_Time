#ifndef ARROWMANAGER_H_
#define ARROWMANAGER_H_
#include <vector>
#include "Arrow.h"

#include "PlayerObject.h"
class ArrowManager
{
public:
	static ArrowManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new ArrowManager();
		}
		return s_pInstance;
	}
	void addEnemyArrow(const GameVector& pos, const GameVector& mapPos, bool isRight);
	const std::vector<Arrow*> getEnemyArrow() { return mEnemyArrows; }
	bool checkCollision(PlayerObject* player);

	void updateArrow();
	void renderArrow();
private:
	ArrowManager();
	~ArrowManager();
	static ArrowManager* s_pInstance;
	std::vector<Arrow*> mEnemyArrows;
};

#endif //ARROWMANAGER_H_

