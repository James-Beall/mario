#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed) : Character(renderer, imagePath, startPosition, map)
{
	mFacingDirection = startFacing;
	mMovementSpeed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;
	mSingleSpriteWidth = mTexture->GetWidth() / 2;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::TakeDamage()
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!mJumping)
	{
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;

		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::Render()
{
	//Variable to hold the left position of the sprite we want to draw.
	int left = 0.0f;

	//If injured move the left position to be the left position of the second image on the spritesheet.
	if (mInjured)
	{
		left = mSingleSpriteWidth;
	}

	//Get the portion of the spritesheet we want to draw.
	//
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

	//Determine where we want it drawn.
	SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	//Then draw it facing the correct direction.
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	else
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	if (!mInjured)
	{
		//We are not injured so move.
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else  if (mFacingDirection == FACING_RIGHT)
		{
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
	else
	{
		//We should not be moving when injured.
		mMovingRight = false;
		mMovingLeft = false;

		//Count down the injured time.
		mInjuredTime -= deltaTime;

		if (mInjuredTime <= 0.0)
		{
			FlipRightWayUp();
		}
	}
}

void CharacterKoopa::FlipRightWayUp()
{
	if (mFacingDirection == FACING_LEFT)
		mFacingDirection = FACING_RIGHT;
	else
		mFacingDirection = FACING_LEFT;
	mInjured = false;
	Jump();
}

bool CharacterKoopa::GetAlive()
{
	return !mInjured;
}

void CharacterKoopa::SetAlive(bool aliveValue)
{
	mInjured = aliveValue;
}
