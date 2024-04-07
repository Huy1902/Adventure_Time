#include "MapManager.h"
#include "MapParser.h"

#include "XmlTree.h"

#include "InteractManager.h"

MapManager* MapManager::s_pInstance = nullptr;

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

GameVector MapManager::changeMapFromTo(int from, int to)
{
	for (Drive& ite : mDriven[from])
	{
		if (ite.to == to)
		{
			mIndexMap = to;
			InteractManager::getInstance()->setSavedPos(GameVector( 0, 0 ), GameVector( ite.x, ite.y ));
			//std::cout << mPlayer->getPosition()->getX() << '\n';
			return GameVector(ite.x, ite.y);
		}
	}
	return GameVector(0, 0);
}

void MapManager::revivePlayer()
{
	GameVector pos = *mPlayer->getPosition();
	delete mPlayer;
	mPlayer = new PlayerObject;
	mPlayer->setPosition(pos);
}

MapManager::MapManager()
{
	Map* temp1 = MapParser::getInstance()->parseMap("map1.tmx");
	Map* temp2 = MapParser::getInstance()->parseMap("map2.tmx");
	mMap.push_back(temp1);
	mMap.push_back(temp2);

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
				ite->takeAttribute("from", &from);
				mDriven[from].push_back(temp);
			}
		}
	}

	mPlayer = new PlayerObject();

}

MapManager::~MapManager()
{
	mMap.clear();
}


