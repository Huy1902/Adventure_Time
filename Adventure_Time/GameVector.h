#ifndef GAMEVECTOR_H_
#define GAMEVECTOR_H_

#include <cmath>

class GameVector
{
public:
	GameVector(float x_, float y_)
	{
		mX = x_;
		mY = y_;
	}
	GameVector() : mX(0), mY(0) {}

	float getX() const { return mX; }
	float getY() const { return mY; }

	void setX(float x) { mX = x; }
	void setY(float y) { mY = y; }

	float getLength() { return std::sqrt(mX * mX + mY * mY); }

	template <typename T>
	GameVector& operator=(const std::pair<T, T>& other)
	{
		mX = static_cast<float> (other.first);
		mY = static_cast<float> (other.second);
		return (*this);
	}
	GameVector operator+(const GameVector& other) const
	{
		return GameVector(mX + other.mX, mY + other.mY);
	}
	GameVector operator-(const GameVector& other) const
	{
		return GameVector(mX - other.mX, mY - other.mY);
	}
	GameVector& operator +=(const GameVector& other)
	{
		mX += other.mX;
		mY += other.mY;
		return (*this);
	}
	GameVector& operator -=(const GameVector& other)
	{
		mX -= other.mX;
		mY -= other.mY;
		return (*this);
	}

private:
	float mX;
	float mY;
};

class GameSize
{
public:
	GameSize(int w_, int h_) : mW(w_), mH(h_)
	{

	}

	void setW(int w) { mW = w; }
	void setH(int h) { mH = h; }
	int getW() const
	{
		return mW;
	}
	int getH() const
	{
		return mH;
	}
private:
	int mW;
	int mH;
};

#endif
