#ifndef RUNACTION_H_
#define RUNACTION_H_
#include "ActionModel.h"
class RunAction :
    public ActionModel
{
public:
	RunAction();
	~RunAction();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);

	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

	virtual void setRightMove(bool b_)
	{
		m_bRight = b_;
	}
private:
};

#endif

