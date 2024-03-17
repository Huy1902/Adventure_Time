#ifndef GAMEVECTOR_H_
#define GAMEVECTOR_H_

#include <cmath>

class GameVector
{
public:
	GameVector(double x_, double y_)
	{
		mX = x_;
		mY = y_;
	}
	GameVector() : mX(0), mY(0) {}

	double getX() const { return mX; }
	double getY() const { return mY; }

	void setX(double x) { mX = x; }
	void setY(double y) { mY = y; }

	double getLength() { return std::sqrt(mX * mX + mY * mY); }

	template <typename T>
	GameVector& operator=(const std::pair<T, T>& other)
	{
		mX = static_cast<double> (other.first);
		mY = static_cast<double> (other.second);
		return (*this);
	}
	GameVector& operator=(const GameVector& other)
	{
		mX = other.mX;
		mY = other.mY;
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
	GameVector& operator *=(const int& other)
	{
		mX *= other;
		mY *= other;
		return (*this);
	}
	GameVector operator / (const int& other)
	{
		return GameVector(mX / other, mY / other);
	}

private:
	double mX;
	double mY;
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
