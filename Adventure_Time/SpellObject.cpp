#include "SpellObject.h"

SpellObject::SpellObject()
{
}

SpellObject::~SpellObject()
{
}

void SpellObject::processData()
{
}

void SpellObject::renderObject() const
{
}

void SpellObject::clearObject()
{
}

void SpellObject::cast()
{
	Info temp = mActions["cast"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}
