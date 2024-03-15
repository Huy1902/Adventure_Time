#include "Layer.h"
#include <iostream>
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
			if(k < layerString.size() && layerString[k] >= '0' && layerString[k] <= '9')
			{
				std::string temp = "";
				while (layerString[k] >= '0' && layerString[k] <= '9')
				{
					temp += layerString[k];
					++k;
				}
				mGrid[i][j] = std::stoi(temp) - 1;
				//std::cout << mGrid[i][j] << ' ';
			}
			else
			{
				++k;
				--j;
			}
		}
		std::cout << '\n';
	}
}

void Layer::renderLayer()
{
	for (int i = 0; i < mNumRow; ++i)
	{
		for (int j = 0; j < mNumCol; ++j)
		{
			if (mGrid[i][j] != -1)
			{
				m_pTileset->renderTile(mGrid[i][j], j * mTileSize, i * mTileSize);
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
}