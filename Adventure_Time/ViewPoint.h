#pragma once

#include "GameVector.h"
class ViewPoint
{
public:
	static ViewPoint* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new ViewPoint();
		}
		return s_pInstance;
	}

	GameVector* getViewPoint()
	{
		return mViewPoint;
	}
	void setPlayerPos(const GameVector& obj)
	{
		*mPlayerPos = obj;
	}

	void updateViewPoint();

private:
	ViewPoint();

	static ViewPoint* s_pInstance;

	GameVector* mPlayerPos;
	GameVector* mViewPoint;
};

