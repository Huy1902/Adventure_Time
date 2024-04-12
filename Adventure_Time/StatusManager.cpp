#include "StatusManager.h"

#include <random>
#include <string>

#include "TextureManager.h"
#include "GameManager.h"
#include "FontManager.h"
#include "ObjectParser.h"

#include "GameVector.h"


using namespace std;
StatusManager* StatusManager::s_pInstance = nullptr;

void StatusManager::updatePlayerStatus()
{
	//mSrcPoint.w = mDestPoint.w = int( ( (*mPlayer->getStatus()).HP * 1.0 / mMaxPlayer.HP) * mLenPoint);
}

void StatusManager::renderPlayerStatus()
{
	Bar temp = mBars["health_point"];
	int w = int( (*mPlayer->getStatus()).HP * 1.0 / (*mPlayer->getMaxStatus()).HP * temp.w );
	TextureManager::getInstance()->drawSinglePic( temp.textureID, temp.x, temp.y, w, temp.h, GameManager::getInstance()->getRenderer());

	temp = mBars["health_bar"];
	TextureManager::getInstance()->drawSinglePic(temp.textureID, temp.x, temp.y, temp.w, temp.h, GameManager::getInstance()->getRenderer());

	temp = mBars["sta_point"];
	w = int( (*mPlayer->getStatus()).STA * 1.0 / (*mPlayer->getMaxStatus()).STA * temp.w );
	TextureManager::getInstance()->drawSinglePic(temp.textureID, temp.x, temp.y, w, temp.h, GameManager::getInstance()->getRenderer());

	temp = mBars["sta_bar"];
	TextureManager::getInstance()->drawSinglePic(temp.textureID, temp.x, temp.y, temp.w, temp.h, GameManager::getInstance()->getRenderer());

	temp = mBars["score"];
	TextureManager::getInstance()->drawSinglePic(temp.textureID, temp.x, temp.y, temp.w, temp.h, GameManager::getInstance()->getRenderer());

	if (mScore < 0)
	{
		mScore = 0;
	}
	string score = to_string(mScore);
	while (score.size() < 5)
	{
		score = "0" + score;
	}
	score = "Score:" + score;
	FontManager::getInstance()->drawText(score.c_str(), temp.x + 47, temp.y + 9);

}
void StatusManager::renderBossStatus()
{
	Bar temp = mBars["boss_point"];
	int w = int((*mBoss->getStatus()).HP * 1.0 / (*mBoss->getMaxStatus()).HP * temp.w);
	TextureManager::getInstance()->drawSinglePic(temp.textureID, temp.x, temp.y, w, temp.h, GameManager::getInstance()->getRenderer());

	temp = mBars["boss_bar"];
	TextureManager::getInstance()->drawSinglePic(temp.textureID, temp.x, temp.y, temp.w, temp.h, GameManager::getInstance()->getRenderer());
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

	int dmg	= int(getDMGtaken(taken->LUCK, cause->ATK, taken->DEF));
	taken->HP -= dmg;
	return (dmg != 0);
}

bool StatusManager::whenEnemyAttackPlayer(EnemyObject* obj)
{
	Status* taken = mPlayer->getStatus();
	Status* cause = obj->getStatus();

	int dmg = int(getDMGtaken(taken->LUCK, cause->ATK, taken->DEF));
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

void StatusManager::renderEnemyStatus(EnemyObject* obj)
{
	Bar temp = mBars["greenbar"];
	int w = int( obj->getStatus()->HP * 1.0 / obj->getMaxStatus()->HP * temp.w );
	TextureManager::getInstance()->drawSinglePic(temp.textureID, int( obj->getPosition()->getX() - obj->getMapPosition()->getX() + obj->getAnimation()->getWidth() / 2 - temp.w / 2 ), 
		int( obj->getPosition()->getY() - obj->getMapPosition()->getY() - temp.w / 2 ), w, temp.h, GameManager::getInstance()->getRenderer());
}

StatusManager::StatusManager()
{
	ObjectParser::getInstance()->parserBar("bar.xml", mBars, mTextures);

	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}

	//mSrcPoint = { 0, 0, mBars["health_point"].w, mBars["health_point"].h}; // 0 0 w h
	//mDestPoint = { mBars["health_point"].x, mBars["health_point"].y, mBars["health_point"].w, mBars["health_point"].h }; // x y w h
	mSrcHealth = { 0, 0, mBars["health_bar"].w, mBars["health_bar"] .h}; // 0 0 w h
	mDestHealth = { mBars["health_bar"].x, mBars["health_bar"].y, mBars["health_bar"].w, mBars["health_bar"].h }; //x y w h

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
	srand(static_cast<unsigned int>(time(NULL)));
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

