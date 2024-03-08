#ifndef RUNACTION_H_
#define RUNACTION_H_
#include "ActionModel.h"
class RunAction :
    public ActionModel
{
	RunAction();
	~RunAction();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);

	//update postition
	virtual void setPos(int x_, int y_)
	{
		mPosition = std::make_pair(x_, y_);
	}

	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();
};

#endif

