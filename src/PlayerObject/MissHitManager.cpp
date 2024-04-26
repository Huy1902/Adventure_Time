#include "MissHitManager.h"
#include "FontManager.h"

MissHitManager* MissHitManager::s_pInstance = nullptr;
void MissHitManager::takeMissHit()
{
	mCountTimeExist = 10;
}

void MissHitManager::renderMissHit()
{
	if (mCountTimeExist > 0)
	{
		--mCountTimeExist;
		FontManager::getInstance()->drawText("Miss a hit", 300, 700);
	}
}
