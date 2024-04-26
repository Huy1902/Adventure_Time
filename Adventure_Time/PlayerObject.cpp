#include "PlayerObject.h"

#include "GameManager.h"

#include "InputManager.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "ObjectParser.h"
#include "SoundManager.h"
#include "StatusManager.h"
#include "AchieveManager.h"

#include "SpellStream.h"
const int HURT_MOVE_BACK = 2;
const int MOVE_SPEED = 10;
const int GRAVITY = 2;
const int UP_FORCE = -20;

const int COST_DASH = 5;
const int COST_ATTACK = 12;

const int STA_RECOVER_SPEED = 1;

std::string  last_sound = "";


PlayerObject::PlayerObject():
	CharModel()
{
	srand(static_cast<time_t>(time(NULL)));
	ObjectParser::getInstance()->parserCharacter("MainCharacter.xml", mActions, mTextures, mSFXs);
	for (const auto& ite : mSFXs)
	{
		SoundManager::getInstance()->loadSound(ite.second.filePath, ite.second.sfxID, SOUND_EFFECT);
	}
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}


	Mix_Volume(mSFXs["run"].channel, 100);
	mStatus.LUCK = 10;
	mStatus.STA = 200;

	mCharHeight = 64;
	mCharWidth = 64;
	mCurrentAction = IDLE;
	mFlip = SDL_FLIP_NONE;
	mAnimation->changeAnim("idle2", 4, mFlip);


	mAnimation->setSize(100, 64);
	mAnimation->setPosition(*mPosition);

	mDyingTime = mActions["dying"].numFrames * mActions["dying"].speed;
	mCountTimeHurt = 0;
	mStatus.EXP = 0;
	mMaxStatus = mStatus;
	mMaxStatus.EXP = 100;

	SpellStream::getInstance()->addSkill("Scourge", SDL_SCANCODE_Q, 20);
	SpellStream::getInstance()->addSkill("Darkra", SDL_SCANCODE_E, 20);
}

PlayerObject::~PlayerObject()
{
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->clearFromTexture(ite.textureID);
	}
	for(const auto&ite : mSFXs)
	{
		SoundManager::getInstance()->clearSFX(ite.second.sfxID);
	}
}

void PlayerObject::processData()
{

	static double start_jump_at_y = 0;
	m_bOnGround = onGround();
	m_bHeadStuck = headStuck();
	//alive
	if (mStatus.isAlive == false)
	{
		--mDyingTime;
		mCurrentAction = DYING;
		completeUpdateMethod();
		return;
	}
	//crit
	if (mCountTimeCrit > 0)
	{
		mCurrentAction = CRIT;
		--mCountTimeCrit;
		AnimationProcess();
		return;
	}

	//able to crit
	if (mCountTimeAbleToCrit > 0)
	{
		--mCountTimeAbleToCrit;
		if (InputManager::getInstance()->keyDown(SDL_SCANCODE_J) && m_bOnGround == true)
		{
			mCountTimeCrit = mActions["crit"].numFrames * mActions["crit"].speed;
			mCurrentAction = CRIT;
			AnimationProcess();
			return;
		}
	}
	//hurt
	if (mCountTimeHurt > 0)
	{
		mCurrentAction = HURT;
		--mCountTimeHurt;
		if (isRight() == true)
		{
			mVelocity->setX(-HURT_MOVE_BACK);
		}
		else
		{
			mVelocity->setX(HURT_MOVE_BACK);
		}
		completeUpdateMethod();
		return;
	}
	else
	{
		mStatus.isInvulnerable = false;
	}
	mVelocity->setX(0);
	//landing
	if (mCountTimeLanding > 0)
	{
		--mCountTimeLanding;
		mCurrentAction = LANDING;
		completeUpdateMethod();
		return;
	}
	//bash
	if (mCountTimeBash > 0)
	{
		--mCountTimeBash;
		mCurrentAction = BASH;
		mVelocity->setX(0);
		completeUpdateMethod();
		return;
	}
	//attack1;
	if (mCountTimeAttack1 > 0)
	{
		--mCountTimeAttack1;
		mCurrentAction = ATTACK1;
		mVelocity->setX(0);
		completeUpdateMethod();
		return;
	}
	//crit
	if (mCountTimeCrit > 0)
	{
		--mCountTimeCrit;
		mCurrentAction = CRIT;
		mVelocity->setX(0);
		completeUpdateMethod();
		return;
	}


	if (mStatus.STA < mMaxStatus.STA)
	{
		mStatus.STA += STA_RECOVER_SPEED;
	}
	if (m_bOnGround == true)
	{
		mVelocity->setY(0);
		mAcceleration->setY(0);
		if (mCurrentAction == FALL || (mCurrentAction == JUMP && start_jump_at_y < mPosition->getY()))
		{
			mCurrentAction = LANDING;
			mCountTimeLanding = mActions["landing"].numFrames * mActions["landing"].speed - 1;
		}
		else
		{
			mCurrentAction = IDLE;
		}
		m_bJump = false;
	}
	else
	{
		mAcceleration->setY(GRAVITY);
	}
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A) == true)
	{
		mVelocity->setX(-MOVE_SPEED);
		mFlip = SDL_FLIP_HORIZONTAL;
		mCurrentAction = RUN;
	}
	else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D) == true)
	{
		mVelocity->setX(MOVE_SPEED);
		mFlip = SDL_FLIP_NONE;
		mCurrentAction = RUN;
	}

	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_K) && m_bOnGround == true && m_bHeadStuck == false)
	{
		m_bOnGround = false;
		m_bJump = true;
		mCurrentAction = JUMP;
		mVelocity->setY(UP_FORCE);
		start_jump_at_y = mPosition->getY();
	}
	else
		if (m_bJump == false && m_bOnGround == false)
		{
			mCurrentAction = FALL;
		}
		else
			if (m_bHeadStuck == true && m_bOnGround == false)
			{
				mVelocity->setY(2);
			}
			else
				if (m_bJump == true)
				{
					mCurrentAction = JUMP;
				}

	//attack1
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_J) && m_bOnGround == true && mStatus.STA > COST_ATTACK * mActions["attack1"].numFrames * mActions["attack1"].speed && mCountTimeAttack1 == 0)
	{
		mCurrentAction = ATTACK1;
		mCountTimeAttack1 = mActions["attack1"].numFrames * mActions["attack1"].speed - 1;
	}
	//dash
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_L) && m_bOnGround == true && mStatus.STA > COST_DASH * mActions["dash"].numFrames * mActions["dash"].speed && mCountTimeDash == 0)
	{
		if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A))
		{
			mVelocity->setX(-MOVE_SPEED * 2);
			mFlip = SDL_FLIP_HORIZONTAL;
			mCurrentAction = DASH;
			mCountTimeDash = mActions["dash"].numFrames * mActions["dash"].speed - 1;
		}
		if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D))
		{
			mVelocity->setX(MOVE_SPEED * 2);
			mFlip = SDL_FLIP_NONE;
			mCurrentAction = DASH;
			mCountTimeDash = mActions["dash"].numFrames * mActions["dash"].speed - 1;
		}
	}
	//bash
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_U) && m_bOnGround == true && mCountTimeBash == 0)
	{
		mCurrentAction = BASH;
		mCountTimeBash = mActions["bash"].numFrames * mActions["bash"].speed;
	}
	//dash
	if (mCountTimeDash > 0)
	{
		--mCountTimeDash;
		mCurrentAction = DASH;
		mVelocity->setX(mVelocity->getX() * 2);
	}
	//side stuck
	if (sideStuck() == 1 && mVelocity->getX() < 0)
	{
		mVelocity->setX(0);
	}
	if (sideStuck() == 2 && mVelocity->getX() > 0)
	{
		mVelocity->setX(0);
	}

	//spell cast
	SpellStream::getInstance()->skillStreamer(*mPosition, this->isRight());
	completeUpdateMethod();
}

void PlayerObject::AnimationProcess()
{
	std::string current_sound = "";
	switch (mCurrentAction)
	{
	case PlayerObject::RUN:
		current_sound = "run";
		run();
		break;
	case PlayerObject::JUMP:
		jump();
		break;
	case PlayerObject::IDLE:
		idle();
		break;
	case PlayerObject::FALL:
		fall();
		break;
	case PlayerObject::ATTACK1:
		mStatus.STA -= COST_ATTACK;
		current_sound = "attack1";
		attack1();
		break;
	case PlayerObject::LANDING:
		landing();
		break;
	case PlayerObject::HURT:
		hurt();
		break;
	case PlayerObject::DASH:
		mStatus.STA -= COST_DASH;
		dash();
		break;
	case PlayerObject::DYING:
		current_sound = "dying";
		dying();
		break;
	case PlayerObject::BASH:
		bash();
		current_sound = "bash";
		break;
	case PlayerObject::CRIT:
		current_sound = "crit";
		crit();
		break;
	default:
		break;
	}

	if (current_sound != last_sound)
	{
		if (last_sound == "run")
		{
			Mix_HaltChannel(mSFXs[last_sound].channel);
		}
		last_sound = current_sound;
	}

	if (Mix_Playing(mSFXs[current_sound].channel))
	{
	}
	else
	{
		SoundManager::getInstance()->playSound(mSFXs[current_sound].sfxID, 0, mSFXs[current_sound].channel);
	}
	mAnimation->update();
}

void PlayerObject::renderObject() const
{
	mAnimation->draw();
}

void PlayerObject::clearObject()
{
}

void PlayerObject::levelUp()
{
	std::cout << "NoName knight level up! Gain ATK, STA and DEF until death!\n";
	mStatus.ATK += 5;
	mMaxStatus.ATK += 5;
	mStatus.DEF += 5;
	mMaxStatus.DEF += 5;
	mMaxStatus.STA += 40;
}

void PlayerObject::getHurt()
{
	std::string current_sound = "";
	if (mStatus.isInvulnerable == false)
	{
		mStatus.isInvulnerable = true;
	}
	if (mStatus.HP <= 0)
	{
		mStatus.isAlive = false;
		mVelocity->setX(0);
		mVelocity->setY(0);
		mAcceleration->setX(0);
		mAcceleration->setY(0);
		StatusManager::getInstance()->setScore(StatusManager::getInstance()->getScore() / 2);
		current_sound = "dying" + std::to_string(rand() % 3);
		SoundManager::getInstance()->playSound(mSFXs[current_sound].sfxID, 0, mSFXs[current_sound].channel);

		AchieveManager::getInstance()->takeAchieve(MAIN_DEATH);
	}
	else
	{
		m_bHurting = true;
		StatusManager::getInstance()->setScore(StatusManager::getInstance()->getScore() - 5);
		if (m_bOnGround == true)
		{
			mCountTimeHurt = mActions["hurt"].numFrames * mActions["hurt"].speed;
		}
		current_sound = "hurt" + std::to_string(rand() % 2);
		if (Mix_Playing(mSFXs[current_sound].channel))
		{
		}
		else
		{
			SoundManager::getInstance()->playSound(mSFXs[current_sound].sfxID, 0, mSFXs[current_sound].channel);
		}
	}
}

bool PlayerObject::onGround()
{
	return CollisionManager::getInstance()->checkPlayerOnGround();
}

bool PlayerObject::headStuck()
{
	if (mFlip == SDL_FLIP_NONE)
	{
		return CollisionManager::getInstance()->checkPlayerHeadStuck(true);
	}
	return CollisionManager::getInstance()->checkPlayerHeadStuck(false);
}

int PlayerObject::sideStuck()
{
	if (CollisionManager::getInstance()->checkPlayerSideLeft() == true)
	{
		return 1;
	}
	else
		if (CollisionManager::getInstance()->checkPlayerSideRight() == true)
		{
			return 2;
		}
	return 0;
}

void PlayerObject::completeUpdateMethod()
{
	AnimationProcess();

	*mVelocity += *mAcceleration;
	*mPosition += *mVelocity;

	mAnimation->setPosition(*mPosition);
}