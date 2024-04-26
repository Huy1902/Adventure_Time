#ifndef ANIMODEL_H_
#define ANIMODEL_H_
#include "BaseModel.h"

#include <vector>
#include <SDL.h>
#include <map>

#include "Animation.h"


class AnimModel :
    public BaseModel
{
public:
	AnimModel();
	virtual  ~AnimModel();

	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();
	Animation* getAnimation()
	{
		return mAnimation;
	}
protected:
	std::map<std::string, Info> mActions;
	Animation* mAnimation;
	std::vector<Texture> mTextures;
	std::map<std::string, SFX> mSFXs;
};

#endif

