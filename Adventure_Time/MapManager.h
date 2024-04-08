#ifndef MAPMANAGER_H_
#define MAPMANAGER_H_

#include "Map.h"

#include "PlayerObject.h"
struct Drive
{
	int to;
	int x;
	int y;
	int map_x;
	int map_y;
};
class MapManager
{
public:
	static MapManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new MapManager();
		}
		return s_pInstance;
	}
	bool nextMap();
	bool previousMap();
	bool beginFirstMap();
	void changeMapFromTo(int from, int to);
	Map* getCurrentMap() const
	{
		return mMap[mIndexMap];
	}
	int getIndexMap() const
	{
		return mIndexMap;
	}
	PlayerObject* getPlayer()
	{
		return mPlayer;
	}

	void revivePlayer();

private:
	MapManager();
	~MapManager();
	static MapManager* s_pInstance;
	int mIndexMap = 0;
	std::vector<Map*> mMap;
	std::vector<std::vector<Drive>> mDriven;

	PlayerObject* mPlayer;
};

#endif;

