#include "MapManager.h"

#include <fstream>

#include "MapParser.h"
#include "XmlTree.h"
#include "InteractManager.h"
#include "AchieveManager.h"

MapManager* MapManager::s_pInstance = nullptr;

using namespace std;

bool MapManager::nextMap()
{
	if (mIndexMap != mMap.size() - 1)
	{
		++mIndexMap;
		return true;
	}
	return false;
}

bool MapManager::previousMap()
{
	if (mIndexMap != 0)
	{
		--mIndexMap;
		return true;
	}
	return false;
}

bool MapManager::beginFirstMap()
{
	return true;
}

void MapManager::changeMapFromTo(int from, int to)
{
	for (Drive& ite : mDriven[from])
	{
		if (ite.to == to)
		{
			mIndexMap = to;
			InteractManager::getInstance()->setSavedPos(GameVector(ite.map_x, ite.map_y), GameVector( ite.x - ite.map_x, ite.y - ite.map_y));
		}
	}
	AchieveManager::getInstance()->takeAchieve(NEW_AREA);
}

void MapManager::revivePlayer()
{
	GameVector pos = *mPlayer->getPosition();
	delete mPlayer;
	mPlayer = new PlayerObject;
	mPlayer->setPosition(pos);
	AchieveManager::getInstance()->takeAchieve(BONFIRE_REVIVAL);
}

MapManager::MapManager()
{
	ifstream fin("list_of_map.txt");
	string mapName;
	while (fin.eof() == false)
	{
		fin >> mapName;
		Map* temp = MapParser::getInstance()->parseMap(mapName);
		mMap.push_back(temp);
	}

	XmlTree tree;
	tree.parseXmlFile("switch_map_driven.xml");
	XmlNode* root = tree.getRoot();
	XmlNode* switches = nullptr;
	for (XmlNode* ite : root->child)
	{
		if (ite->element == "SWITCHES")
		{
			switches = ite;
			break;
		}
	}
	int n;
	switches->takeAttribute("numberMap", &n);
	mDriven.resize(n);
	if (switches != nullptr)
	{
		for (XmlNode* ite : switches->child)
		{
			if (ite->element == "switch")
			{
				Drive temp;
				int from;
				ite->takeAttribute("x", &temp.x);
				ite->takeAttribute("y", &temp.y);
				ite->takeAttribute("to", &temp.to);
				ite->takeAttribute("map_x", &temp.map_x);
				ite->takeAttribute("map_y", &temp.map_y);
				ite->takeAttribute("from", &from);
				mDriven[from].push_back(temp);
			}
		}
	}

	mPlayer = new PlayerObject();

}

MapManager::~MapManager()
{
	delete mPlayer;
	mMap.clear();
}


