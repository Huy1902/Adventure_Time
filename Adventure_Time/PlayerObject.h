#ifndef PLAYEROBJECT_H_
#define PLAYEROBJECT_H_
#include "ObjectModel.h"

#include "ActionMachine.h"

class PlayerObject :
    public ObjectModel
{
public:
	PlayerObject();
	~PlayerObject();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

	ActionMachine* getActionMachine()
	{
		return mActionMachine;
	}
	static PlayerObject* getPlayerObject()
	{
		return this;
	}

private:
	bool m_bOnAir;

	ActionMachine* mActionMachine;
};

#endif
