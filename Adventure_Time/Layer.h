#pragma once

#include <vector>
#include <string>

#include "Tileset.h"

class Layer
{
public:
	Layer(const std::string& layerString, const int& row, const int& col, const int& tileSize);
	~Layer();

	void renderLayer();
	void setTileset(Tileset* pTileSet)
	{
		m_pTileset = pTileSet;
	}
private:
	std::vector<std::vector<int>> mGrid;
	int mNumRow;
	int mNumCol;
	int mTileSize;
	Tileset* m_pTileset;
};

