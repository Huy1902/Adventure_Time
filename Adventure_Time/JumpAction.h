#ifndef JUMPACTION_H_
#define JUMPACTION_H_
#include "ActionModel.h"

class JumpAction :
    public ActionModel
{
public:
	JumpAction();
	~JumpAction();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);

	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();
};

#endif

