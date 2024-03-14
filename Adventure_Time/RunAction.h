#ifndef RUNACTION_H_
#define RUNACTION_H_
#include "ActionModel.h"
class RunAction :
    public ActionModel
{
public:
	RunAction();
	~RunAction();


	virtual void setCallback(void(*callback)()) { mCallback = callback; }
	virtual void processData();
	virtual void renderAction();
	virtual bool onEnter();
	virtual bool onExit();
	std::string getActionID() const { return mActionID; }
private:
	void mFromRunToJump();
	void mFromRunToDash();
	void mFromRunToIdle();

	GameVector* mVelocity;

	std::string mTextureID;
};

#endif

