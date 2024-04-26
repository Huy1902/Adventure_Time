#pragma once


#include <vector>
#include <string>
class Tileset
{
public:
	Tileset(const std::string& filePath, const std::string& id, int tileSize, int w, int h);
	~Tileset();

	void renderTile(const int& id, const int& x, const int& y) const;
	void renderPartOfTile(const int& id, const int& x, const int& y, const int& xSrc, const int& wSrc) const;
	int getNumTile() const { return mNumTile; }
	int getTileSize() const { return mTileSize; }
private:
	int mTileSize;
	int mWidth;
	int mHeight;
	int mNumRow;
	int mNumCol;
	int mNumTile;
	std::string mID;
};

