//#pragma once
//
//#include <vector>
//
//#include "PlayerObject.h"
//#include "EnemyObject.h"
//
//class ObjectLayer
//{
//public:
//	void renderLayer();
//	void updateLayer();
//
//	//void setVelocity(const GameVector& obj)
//	//{
//	//	*mVelocity = obj;
//	//}
//	//void setVelocityX(const double & x_)
//	//{
//	//	mVelocity->setX(x_);
//	//}
//	//void setVelocityY(const double& y_)
//	//{
//	//	mVelocity->setX(y_);
//	//}
//	void setPosition(const GameVector& obj)
//	{
//		*mPosition = obj;
//	}
//	GameVector* getPosition()
//	{
//		return mPosition;
//	}
//	int getID(const double& x, const double& y) const;
//	void optimizePositionY(double& y);
//private:
//	PlayerObject* mPlayer;
//	std::vector<EnemyObject*> mEnemy;
//};
//
