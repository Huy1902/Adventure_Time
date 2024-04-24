#include "Layer.h"
#include <iostream>

const int WINDOWS_ROW = 24;
const int WINDOWS_COL = 40;

Layer::Layer(const std::string& layerString, const int& numRow, const int& numCol, const int& tileSize) :
	mNumRow(numRow),
	mNumCol(numCol),
	mTileSize(tileSize),
	m_pTileset(nullptr)
{
	mGrid.resize(numRow);
	for (int i = 0; i < numRow; ++i)
	{
		mGrid[i].resize(numCol);
	}
	int k = 0;
	for (int i = 0; i < numRow; ++i)
	{
		for (int j = 0; j < numCol; ++j)
		{
			if (k < layerString.size() && layerString[k] >= '0' && layerString[k] <= '9')
			{
				std::string temp = "";
				while (layerString[k] >= '0' && layerString[k] <= '9')
				{
					temp += layerString[k];
					++k;
				}
				mGrid[i][j] = std::stoi(temp) - 1;
			}
			else
			{
				++k;
				--j;
			}
		}
	}
	mPosition = new GameVector(0, 0);
}

Layer::Layer(const std::string& layerString, const int& numRow, const int& numCol) :
	mNumRow(numRow),
	mNumCol(numCol),
	m_pTileset(nullptr)
{
	mGrid.resize(numRow);
	for (int i = 0; i < numRow; ++i)
	{
		mGrid[i].resize(numCol);
	}
	int k = 0;
	for (int i = 0; i < numRow; ++i)
	{
		for (int j = 0; j < numCol; ++j)
		{
			if (k < layerString.size() && layerString[k] >= '0' && layerString[k] <= '9')
			{
				std::string temp = "";
				while (layerString[k] >= '0' && layerString[k] <= '9')
				{
					temp += layerString[k];
					++k;
				}
				mGrid[i][j] = std::stoi(temp) - 1;
			}
			else
			{
				++k;
				--j;
			}
		}
	}
	mPosition = new GameVector(0, 0);
}

void Layer::updateLayer()
{
}

int Layer::getID(const double& x, const double& y) const
{
	int x_p = (mPosition->getX() / mTileSize) + (x / mTileSize);
	int y_p = (mPosition->getY() / mTileSize) + (y / mTileSize);

	return mGrid[y_p][x_p];
}

int Layer::getIDNoBaseOnMap(const double& x, const double& y) const
{
	int x_p = x / mTileSize;
	int y_p = y / mTileSize;
	return mGrid[y_p][x_p];
}

void Layer::optimizePositionY(double& y)
{
	y = floor(y / mTileSize);
	y = y * mTileSize;
}

void Layer::renderLayer()
{
	int x = mPosition->getX() / mTileSize;
	int y = mPosition->getY() / mTileSize;

	int edge_end_witdth = (int)mPosition->getX() % mTileSize;
	int edge_start_width = mTileSize - edge_end_witdth;
	int w2 = edge_end_witdth;
	int w1 = edge_start_width;
	for (int i = 0; i < WINDOWS_ROW; ++i)
	{
		if (mGrid[i + y][0 + x] != -1)
		{
			m_pTileset->renderPartOfTile(mGrid[i + y][0 + x], 0 * mTileSize, i * mTileSize, w2, w1);
		}
	}
	for (int i = 0; i < WINDOWS_ROW; ++i)
	{
		for (int j = 1; j <= WINDOWS_COL; ++j)
		{
			if (mGrid[i + y][j + x] != -1)
			{
				m_pTileset->renderTile(mGrid[i + y][j + x], j * mTileSize - w2, i * mTileSize);
			}
		}
	}
}

Layer::~Layer()
{
	for (int i = 0; i < mGrid.size(); ++i)
	{
		mGrid[i].clear();
	}
	mGrid.clear();
	delete mPosition;
}