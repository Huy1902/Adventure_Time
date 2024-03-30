#pragma once

#include <vector>
#include <string>

#include "Tileset.h"
#include "GameVector.h"


class Layer
{
public:
	Layer(const std::string& layerString, const int& numRow, const int& numCol, const int& tileSize);
	Layer(const std::string& layerString, const int& numRow, const int& numCol);
	~Layer();

	void renderLayer();
	void setTileset(Tileset* pTileSet)
	{
		m_pTileset = pTileSet;
		mTileSize = pTileSet->getTileSize();
	}
	void updateLayer();

	void setPosition(const GameVector& obj)
	{
		*mPosition = obj;
	}
	GameVector* getPosition()
	{
		return mPosition;
	}
	int getID(const double &x, const double& y) const;
	void optimizePositionY(double& y);
private:
	std::vector<std::vector<int>> mGrid;
	int mNumRow;
	int mNumCol;
	int mTileSize;
	Tileset* m_pTileset;

	GameVector* mPosition;
};

