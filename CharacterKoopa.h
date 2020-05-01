#pragma once
#include "Character.h"
#include "LevelMap.h"
#include "Commons.h"
#include "Texture2D.h"
#include "Constants.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFacing, float movementSpeed);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	bool GetAlive();
	void SetAlive(bool aliveValue);
private:
	void FlipRightWayUp();
	
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	bool mInjured;
	float mInjuredTime;
	float mMovementSpeed;

	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
};

