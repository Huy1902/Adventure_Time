#include "Command.h"
#include <iostream>

#include "MissHitManager.h"
#include "MapManager.h"


using namespace std;

void DefeatEnemyCommand::execute()
{
	cout << "Defeat enemy\nGain ATK, STA until death\n";
	MapManager::getInstance()->getCurrentMap()->getPlayer()->getStatus()->ATK += 1;
	MapManager::getInstance()->getCurrentMap()->getPlayer()->getmMaxStatus()->ATK += 1;
	MapManager::getInstance()->getCurrentMap()->getPlayer()->getmMaxStatus()->STA += 20;
}

void FirstBossCommand::execute()
{
	cout << "You defeat first boss\nGain ATK until death\n";
	MapManager::getInstance()->getCurrentMap()->getPlayer()->getStatus()->ATK += 10;
	MapManager::getInstance()->getCurrentMap()->getPlayer()->getmMaxStatus()->ATK += 10;
}

void MissCommand::execute()
{
	MissHitManager::getInstance()->takeMissHit();
}
