#include "Tileset.h"

#include "TextureManager.h"
#include "GameManager.h"

Tileset::Tileset(const std::string& fileName, const std::string& tileID, int tileSize, int w, int h) : 
	mTileSize(tileSize),
	mWidth(w),
	mHeight(h),
	mID(tileID)
{
	TextureManager::getInstance()->load(fileName, tileID, GameManager::getInstance()->getRenderer());
	mNumCol = mWidth / mTileSize;
	mNumRow = mHeight / mTileSize;
	isground.resize(1000, false);
	mNumTile = mNumCol * mNumRow;
}

void Tileset::renderTile(const int & id, const int & x, const int & y) const
{
	int src_x = id % mNumCol;
	int src_y = id / mNumCol;
	//TextureManager::getInstance()->drawSpritePicByCol(mID, x * mTileSize, y * mTileSize, mTileSize, mTileSize,
	//	GameManager::getInstance()->getRenderer(), 1);

	SDL_Rect srcRect = { src_x * mTileSize, src_y * mTileSize, mTileSize, mTileSize };
	SDL_Rect destRect = { x, y, mTileSize, mTileSize };

	SDL_RenderCopyEx(GameManager::getInstance()->getRenderer(), TextureManager::getInstance()->getTexture(mID), &srcRect, &destRect, NULL, NULL, SDL_FLIP_NONE);
}

void Tileset::renderPartOfTile(const int& id, const int& x, const int& y, const int& xSrc, const int& wSrc) const
{
	int src_x = id % mNumCol;
	int src_y = id / mNumCol;

	SDL_Rect srcRect = { src_x * mTileSize + xSrc, src_y * mTileSize, wSrc, mTileSize };
	SDL_Rect destRect = { x, y, wSrc, mTileSize };
	SDL_RenderCopyEx(GameManager::getInstance()->getRenderer(), TextureManager::getInstance()->getTexture(mID), &srcRect, &destRect, NULL, NULL, SDL_FLIP_NONE);
}

void Tileset::setGround(const std::vector<int>& ground)
{
	for (const int& id : ground)
	{
		isground[id] = true;
	}
}

bool Tileset::isGround(const int& id)
{
	return isground[id];
}

Tileset::~Tileset()
{
	TextureManager::getInstance()->clearFromTexture(mID);
	isground.clear();
}

