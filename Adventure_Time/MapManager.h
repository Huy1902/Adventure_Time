#ifndef MAPMANAGER_H_
#define MAPMANAGER_H_

#include "Map.h"

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

	Map* getCurrentMap() const
	{
		return mMap[mCurrentMap];
	}

private:
	MapManager();
	~MapManager();
	static MapManager* s_pInstance;
	std::vector<Map*> mMap;
	int mCurrentMap;
};

#endif;

