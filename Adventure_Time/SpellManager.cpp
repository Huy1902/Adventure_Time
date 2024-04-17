#include "SpellManager.h"
#include "CollisionManager.h"
#include "StatusManager.h"
#include "GeneratorManager.h"
SpellManager* SpellManager::s_pInstance = nullptr;

using namespace std;



void SpellManager::addPlayerSpell(const std::string nameSpell, const GameVector& pos, const GameVector& mapPos, bool isRight)
{
	SpellObject* obj = dynamic_cast<SpellObject*>(GeneratorManager::getInstance()->generatorObject(nameSpell));
	obj->setPosition(pos);
	obj->setMapPosition(mapPos);
	mPlayerSpell.push_back(obj);
}

bool SpellManager::checkCollisionWithPlayerSpell(EnemyObject* enemy)
{
	vector<SpellObject*>::iterator ite = mPlayerSpell.begin();
	while (ite != mPlayerSpell.end())
	{
		SDL_Rect spellRect{ (*ite)->getPosition()->getX(), (*ite)->getPosition()->getY(),
			(*ite)->getAnimation()->getWidth(), (*ite)->getAnimation()->getHeight() };
		SDL_Rect playerRect{ enemy->getPosition()->getX(), enemy->getPosition()->getY(), enemy->getAnimation()->getWidth(), enemy->getAnimation()->getHeight() };
		if (SDL_HasIntersection(&spellRect, &playerRect))
		{
			if (StatusManager::getInstance()->whenSpellAttackEnemy((*ite), enemy) == true)
			{
				enemy->getHurt();
			}
		}
		if ((*ite)->isExist() == false)
		{
			ite = mPlayerSpell.erase(ite);
		}
		else
		{
			(*ite)->processData();
			++ite;
		}
	}
	return false;
}

void SpellManager::updateSpell()
{
	vector<SpellObject*>::iterator ite = mPlayerSpell.begin();
	while (ite != mPlayerSpell.end())
	{
		if ((*ite)->isExist() == false)
		{
			ite = mPlayerSpell.erase(ite);
		}
		else
		{
			(*ite)->processData();
			++ite;
		}
	}
}

void SpellManager::renderSpell()
{
	for (SpellObject* ite : mPlayerSpell)
	{
		ite->renderObject();
	}
}

SpellManager::SpellManager()
{
}
