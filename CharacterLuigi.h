#pragma once
#include "Character.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imgPath, Vector2D startPosition, LevelMap* map);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e);
	void Render();

private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
};

