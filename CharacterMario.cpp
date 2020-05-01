#include "CharacterMario.h"
#include "Texture2D.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imgPath, Vector2D startPosition, LevelMap* map) : Character(renderer, imgPath, startPosition, map)
{
//	mRenderer = renderer;
//	mPosition = startPosition;
//	mTexture = new Texture2D(mRenderer);
//	if (!mTexture->LoadFromFile(imgPath))
//	{
//		std::cout << "Failed to load character texture";
//	}
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
    mCurrentLevelMap = map;
	//setposition(startposition)
}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
    //Collision position variables.
    int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
    int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

    //Deal with gravity.
    if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
    {
        AddGravity(deltaTime);
        //std::cout << "test output 1" << std::endl;
    }
    else
    {
        //Collided with ground so we can jump again.
        mCanJump = true;
        //std::cout << "test output 2" << std::endl;
    }
   //Deal with jumping first.
   if (mJumping)
   {
       //Adjust the position.
       mPosition.y -= mJumpForce * deltaTime;

       //Reduce the jump force.
       mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

       //Has the jump force reduced to zero?
       if (mJumpForce <= 0.0f)
       {          
          mJumping = false;
          std::cout << mPosition.y;
       }
   }
//
//   //if (mMovingLeft)
//   //{
//   //    MoveLeft(deltaTime);
//   //    //std::cout << "Calling MoveLeft" << std::endl;
//   //}
//   //else if (mMovingRight)
//   //{
//   //    MoveRight(deltaTime);
//   //    //std::cout << "Calling MoveRight" << std::endl;
//   //}
   switch (e.type)
    {
        case SDL_KEYDOWN:
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_LEFT:
                {
                    MoveLeft(deltaTime);
                    mFacingDirection = FACING_LEFT;
                    //std::cout << "Moving left key pressed" << std::endl;
                    break;
                }
                case SDLK_UP:
                {
                    Jump();
                    //std::cout << "Moving jump key pressed" << std::endl;
                    break;
                }
                case SDLK_RIGHT:
                {
                    MoveRight(deltaTime);
                    mFacingDirection = FACING_RIGHT;
                    //std::cout << "Moving Right key pressed" << std::endl;
                    break;
                }
            }
        break;
        }
    }
   	if (mPosition.y <= -1000) {
		AddGravity(deltaTime);
	}
}

void CharacterMario::Render()
{
	if (mFacingDirection == FACING_RIGHT)
    {
        mTexture->Render(mPosition, SDL_FLIP_NONE);
		  //mTexture->Render(GetPosition(), SDL_FLIP_NONE, 0);
    }
    else
    {
        mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL);
		  //mTexture->Render(GetPosition(), SDL_FLIP_HORIZONTAL, 0);
    }
}
CharacterMario::~CharacterMario()
{
	//mRenderer = NULL;
}