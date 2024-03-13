#ifndef ACTIONMODEL_H_
#define ACTIONMODEL_H_

#include "BaseAction.h"

class ActionModel :
	public BaseAction
{
public:
	ActionModel();
	~ActionModel();

	virtual void setCallback(void(*callback)()) { mCallback = callback; }
	virtual void processData();
	virtual void renderAction();
	virtual bool onEnter();
	virtual bool onExit();
	std::string getActionID() const { return mActionID; }


protected:
	static std::string mActionID;
	void(*mCallback)();
	bool m_bRight;
	
	int mIndexFrames;
	int mNumFrames;

	GameVector* mPosition;

	int mWidth;
	int mHeight;

};
#endif
