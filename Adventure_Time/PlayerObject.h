#ifndef PLAYEROBJECT_H_
#define PLAYEROBJECT_H_
#include "ObjectModel.h"

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

private:
	bool m_bOnAir;


	GameVector* mVelocity;
	GameVector* mAcceleration;

	bool m_bRight;


	std::map<std::string, ActionModel*> mActionMap;
	ActionModel* mCurrentAction;
};

#endif
