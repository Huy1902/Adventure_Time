#include "StatusManager.h"

#include <random>
#include <string>

#include "TextureManager.h"
#include "GameManager.h"

#include "FontManager.h"
#include "GameVector.h"

using namespace std;
StatusManager* StatusManager::s_pInstance = nullptr;

void StatusManager::updatePlayerStatus()
{
	mCurrentPlayer = *mPlayer->getStatus();
	mSrcPoint.w = mDestPoint.w = (mCurrentPlayer.HP * 1.0 / mMaxPlayer.HP) * mLenPoint;
}

void StatusManager::renderPlayerStatus()
{
	SDL_RenderCopy(GameManager::getInstance()->getRenderer(), TextureManager::getInstance()->getTexture("health_point"), &mSrcPoint, &mDestPoint);
	SDL_RenderCopy(GameManager::getInstance()->getRenderer(), TextureManager::getInstance()->getTexture("health_bar"), & mSrcHealth, &mDestHealth);
}

void StatusManager::setPlayer(PlayerObject* obj)
{
	mPlayer = obj;
	mMaxPlayer = *obj->getStatus();
}

bool StatusManager::whenPlayerAttackEnemy(EnemyObject* obj)
{
	Status* taken = obj->getStatus();
	Status* cause = mPlayer->getStatus();

	int dmg	= getDMGtaken(taken->LUCK, cause->ATK, taken->DEF);
	taken->HP -= dmg;
	return (dmg != 0);
}

bool StatusManager::whenEnemyAttackPlayer(EnemyObject* obj)
{
	Status* taken = mPlayer->getStatus();
	Status* cause = obj->getStatus();

	int dmg = getDMGtaken(taken->LUCK, cause->ATK, taken->DEF);
	taken->HP -= dmg;
	return (dmg != 0);
}

void StatusManager::renderOnGamePause()
{
	mCurrentPlayer = *mPlayer->getStatus();

	string hp = to_string(mCurrentPlayer.HP);
	hp += " / ";
	hp += to_string(mMaxPlayer.HP);
	FontManager::getInstance()->drawText(hp.c_str(), 500, 330);

	string sta = to_string(mCurrentPlayer.STA);
	sta += " / ";
	sta += to_string(mMaxPlayer.STA);
	FontManager::getInstance()->drawText(sta.c_str(), 500, 397);

	string atk = to_string(mCurrentPlayer.ATK);
	atk += " / ";
	atk += to_string(mMaxPlayer.ATK);
	FontManager::getInstance()->drawText(atk.c_str(), 500, 467);

	string def = to_string(mCurrentPlayer.DEF);
	def += " / ";
	def += to_string(mMaxPlayer.DEF);
	FontManager::getInstance()->drawText(def.c_str(), 835, 330);

	string iq = to_string(mCurrentPlayer.IQ);
	iq += " / ";
	iq += to_string(mMaxPlayer.IQ);
	FontManager::getInstance()->drawText(iq.c_str(), 835, 397);

	string luck = to_string(mCurrentPlayer.LUCK);
	luck += " / ";
	luck += to_string(mMaxPlayer.LUCK);
	FontManager::getInstance()->drawText(luck.c_str(), 835, 467);

	string exp = to_string(mCurrentPlayer.EXP);
	exp += " / ";
	exp += to_string(mMaxPlayer.EXP);
	FontManager::getInstance()->drawText(hp.c_str(), 630, 206);
	avatar->update();
	avatar->draw();
}

StatusManager::StatusManager()
{
	TextureManager::getInstance()->load("assets/status/health_bar.png", "health_bar", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/status/health_point.png", "health_point", GameManager::getInstance()->getRenderer());
	mSrcPoint = { 0, 0, 140, 10 };
	mDestPoint = { 47, 27, 140, 10 };
	mSrcHealth = { 0, 0, 190, 57 };
	mDestHealth = { 0, 0, 190, 57 };

	mLenPoint = mSrcPoint.w;

	avatar = new Animation();
	avatar->changeAnim("run2", 7, SDL_FLIP_NONE, 100, 64, 2);

	GameVector temp({ 380, 225 });
	avatar->setPosition(temp);
}

StatusManager::~StatusManager()
{
	delete avatar;
}

double StatusManager::getDMGtaken(const int& luck, const int& atk, const int& def)
{
	srand(time(0));
	int random = rand() % 100 + 1;
	double dmg_taken;
	if (random <= luck)
	{
		dmg_taken = 0;
	}
	else
	{
		dmg_taken = (1.0 - 1.0 * def / 100) * atk;
	}
	return dmg_taken;
}

