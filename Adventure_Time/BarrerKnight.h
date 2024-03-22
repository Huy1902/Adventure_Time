#ifndef BARRERKNIGHT_H_
#define BARRERKNIGHT_H_
#include "EnemyObject.h"

#include "Animation.h"

#include <SDL.h>

class BarrerKnight :
    public EnemyObject
{

public:

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();
	virtual void setMapPosition(const GameVector& pos)
	{
		*mMapPosition = pos;
	}

	BarrerKnight();
	~BarrerKnight();

private:

	GameVector* mVelocity;
	GameVector* mAcceleration;



	bool m_bRight;


	int mCharHeight;
	int mCharWidth;

	int mTimeRun;

	bool onGround();
	//int sideStuck();

	bool m_bHeadStuck;
	bool m_bRun;
	bool m_bOnGround;
	

	void AnimationProcess();

	enum Action
	{
		RUN = 0,
		IDLE = 2,
		FALL = 3,
		WAKE_UP = 4
	};

	Action mCurrentAction;
	Action mBackAction;

	Animation* animation;

	void run();
	void none();
	void wakeUp();
};

#endif

