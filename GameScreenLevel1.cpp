#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
#include "Collisions.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mRenderer = renderer;
	mLevelMap = NULL;
	SetUpLevel();
}

void GameScreenLevel1::Render()
{
	//Draw the enemies.
	for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}

	//Draws the background.
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);

	mario->Render();
	luigi->Render();
	mPowBlock->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//-----------------------------------
	// Do the screen shake if required.
	//-----------------------------------
	if (mScreenshake)
	{
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		//End the shake after the duration.
		if (mScreenshakeTime <= 0.0f)
		{
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}


	//Update the player.
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
	UpdatePowBlock();
	UpdateEnemies(deltaTime, e);

	//if (Collisions::Instance()->Circle(mario, luigi));
	//if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()));

	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		std::cout << "Box collison" << std::endl;
	}
}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instance()->Box(mario->GetCollisionBox(),mPowBlock->GetCollisionBox()))
	{
		
		if (mPowBlock->IsAvailable())
		{
			std::cout << "Colliding with POW" << std::endl;
			//Collided whilst jumping.
			if (!mario->IsJumping())
			{
				DoScreenShake();
				mPowBlock->TakeAHit();
				mario->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	//----------------------
	// Update the Enemies.
	//----------------------

	if (!mEnemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mEnemies.size(); i++)
		{
			//Check if enemy is on the bottom row of tiles.
			if (mEnemies[i]->GetPosition().y > 300.0f)
			{
				//Is the enemy off screen to the left / right?
				if (mEnemies[i]->GetPosition().x < (float)(-mEnemies[i]->GetCollisionBox().width * 0.5f) || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(mEnemies[i]->GetCollisionBox().width * 0.55f))mEnemies[i]->SetAlive(false);
				{

				}
			}

			

			//Check to see if the enemy collides with the player.
			else if ((mEnemies[i]->GetPosition().y > 300.0f || mEnemies[i]->GetPosition().y <= 64.0f) && (mEnemies[i]->GetPosition().x < 64.0f || mEnemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f));
			{
				//Ignore the collisions if the enemy is behind a pipe?
			}
			//If the enemy is no longer alive the schedule it for deletion.
			if (!mEnemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
			else 
			{
				if (Collisions::Instance()->Circle(mEnemies[i], mario))
				{
					//mario->SetState(CHARACTERSTATE_PLAYER_DEATH);
				}
			}

			//Now do the update.
			mEnemies[i]->Update(deltaTime, e);


		}
		//---------------------------------------
		// Remove a dead enemy - 1 each update.
		//---------------------------------------
		if (enemyIndexToDelete != -1)
		{
			mEnemies.erase(mEnemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopaCharacter = new CharacterKoopa(mRenderer, "Images/Koopa.png", position, mLevelMap, direction, speed);

	mEnemies.push_back(koopaCharacter);

	/*for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		
	}*/
}

bool GameScreenLevel1::SetUpLevel()
{
	//Create the level map.
	SetLevelMap();

	//Set up the player characters.
	mario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(64, 330),  mLevelMap);
	//std::cout << "Test" << std::endl;
	luigi = new CharacterLuigi(mRenderer, "Images/Luigi.png",  Vector2D(164, 330), mLevelMap);

	//Set up the Pow Block.
	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	//Set up 2 bad guys.
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {

		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} 
	};

	//Clear up any old map.
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	//Set the new one.
	mLevelMap = new LevelMap(map);
}

void GameScreenLevel1::DoScreenShake()
{
	for (unsigned int i = 0; i < mEnemies.size(); i++) {
		mEnemies[i]->TakeDamage();
	}
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete mBackgroundTexture;
	mBackgroundTexture = NULL;

	delete mario;
	mario = NULL;

	delete luigi;
	luigi = NULL;

	delete mPowBlock;
	mPowBlock = NULL;

	mEnemies.clear();
}