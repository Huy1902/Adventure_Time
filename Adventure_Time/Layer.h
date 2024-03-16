#pragma once

#include <vector>
#include <string>

#include "Tileset.h"
#include "GameVector.h"


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
	void updateLayer();

	void setVelocity(const GameVector& obj)
	{
		*mVelocity = obj;
	}
	void setVelocityX(const double & x_)
	{
		mVelocity->setX(x_);
	}
	void setVelocityY(const double& y_)
	{
		mVelocity->setX(y_);
	}
private:
	std::vector<std::vector<int>> mGrid;
	int mNumRow;
	int mNumCol;
	int mTileSize;
	Tileset* m_pTileset;

	GameVector* mPosition;
	GameVector* mVelocity;
};

