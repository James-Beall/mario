#pragma once
#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include "Constants.h"
#include "LevelMap.h"

class Texture2D; //Forward Declaration

class Character
{
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	bool mJumping;
	bool mCanJump;
	float mJumpForce;

	float mCollisionRadius;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	void AddGravity(float deltaTime);
	void Jump();

public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	float GetCollisionRadius();

	Rect2D GetCollisionBox();

	bool IsJumping();
	void CancelJump();

private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;

	LevelMap* mCurrentLevelMap;
};