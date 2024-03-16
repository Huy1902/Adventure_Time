//#include "ViewPoint.h"
//
//#include "iostream"
//class ViewPoint
//{
//public:
//	static ViewPoint* getInstance()
//	{
//		if (s_pInstance == nullptr)
//		{
//			s_pInstance = new ViewPoint();
//		}
//		return s_pInstance;
//	}
//
//	GameVector* getViewPoint()
//	{
//		return mViewPoint;
//	}
//	void setPlayerPos(const GameVector& obj)
//	{
//		*mPlayerPos = obj;
//	}
//
//	void updateViewPoint();
//
//private:
//	ViewPoint();
//	~ViewPoint();
//
//	static ViewPoint* s_pInstance;
//
//	GameVector* mPlayerPos;
//	GameVector* mViewPoint;
//};
//const int WINDOW_WIDTH = 1280;
//const int WINDOW_HEIGHT = 768;
//
//ViewPoint* ViewPoint::s_pInstance = nullptr;
//
//ViewPoint::ViewPoint()
//{
//	mPlayerPos = new GameVector();
//	mViewPoint = new GameVector();
//}
//
//void ViewPoint::updateViewPoint()
//{
//	if (mPlayerPos != nullptr)
//	{
//		mViewPoint->setX(mPlayerPos->getX() - WINDOW_WIDTH / 2);
//		mViewPoint->setY(mPlayerPos->getY() - WINDOW_HEIGHT / 2);
//	}
//}
//
//ViewPoint::~ViewPoint()
//{
//	delete mViewPoint;
//	delete mPlayerPos;
//}