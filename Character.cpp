#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, std::string imgPath, Vector2D startPosition, LevelMap* map)
{
    mRenderer = renderer;
    mPosition = startPosition;
    mTexture = new Texture2D(mRenderer);
    if (!mTexture->LoadFromFile(imgPath))
    {
        std::cout << "Failed to load character texture";
    }
    mFacingDirection = FACING_RIGHT;
    mMovingLeft = false;
    mMovingRight = false;
    mCollisionRadius = 15.0f;
    mCurrentLevelMap = map;
}

void Character::Render()
{

}

void Character::MoveLeft(float deltaTime)
{
        mPosition.x -= 5.f;
        //std::cout << "Moving Left" << std::endl;
}

void Character::MoveRight(float deltaTime)
{
        mPosition.x += 5.f;
        //std::cout << "Moving Right" << std::endl;
}

void Character::AddGravity(float deltaTime)
{
  /*  if (mPosition.y < -1080)
    {
        mPosition.y = gravity * deltaTime;
        mCanJump = false;
    }
*/
    mPosition.y += deltaTime * GRAVITY;
    mCanJump = false;
}

void Character::Jump()
{
    std::cout << "Jump Function Called" << std::endl;
	if (!mJumping) {
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
    //Collision position variables.
    int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth() * 0.5f)) / TILE_WIDTH;
    int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

    //Deal with gravity.
    if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
    {
        AddGravity(deltaTime);
    }
    else
    {
        //Collided with ground so we can jump again.
        mCanJump = true;
    }
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
}

void Character::SetPosition(Vector2D newPosition)
{
    mPosition = newPosition;
}

Vector2D Character::GetPosition()
{
    return mPosition;
}

float Character::GetCollisionRadius()
{
    return mCollisionRadius;
}

Rect2D Character::GetCollisionBox()
{
    return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}

bool Character::IsJumping()
{
	return false;
}

void Character::CancelJump()
{
    return;
}

Character::~Character()
{
    mRenderer = NULL;
}