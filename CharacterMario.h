#pragma once
#include "Character.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imgPath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e);
	void Render();

private:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;

	LevelMap* mCurrentLevelMap;
};

