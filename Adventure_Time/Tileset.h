#pragma once


#include <vector>
#include <string>
class Tileset
{
public:
	Tileset(const std::string& fileName, const std::string& id, int tileSize, int w, int h);
	~Tileset();

	void renderTile(const int& id, const int& x, const int& y) const;
	void renderPartOfTile(const int& id, const int& x, const int& y, const int& xSrc, const int& wSrc) const;
	void setGround(const std::vector<int>& ground);
	bool isGround(const int& id);
	int getNumTile() const { return mNumTile; }
private:
	int mTileSize;
	int mWidth;
	int mHeight;
	int mNumRow;
	int mNumCol;
	int mNumTile;
	std::vector<bool> isground;
	std::string mID;
};

