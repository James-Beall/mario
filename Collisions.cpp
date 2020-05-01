#include "Collisions.h"
#include "Character.h"

//Initialise the instance to null.
Collisions* Collisions::mInstance = NULL;

Collisions::Collisions()
{

}

Collisions* Collisions::Instance()
{
	if (!mInstance)
	{
		mInstance = new Collisions;
	}

	return mInstance;
}

bool Collisions::Circle(Character* mario, Character* luigi)
{
	Vector2D vec = Vector2D((mario->GetPosition().x - luigi->GetPosition().x), (mario->GetPosition().y - luigi->GetPosition().y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combinedDistance = (mario->GetCollisionRadius() + luigi->GetCollisionRadius());

	return distance < combinedDistance;

	return false;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.x + (rect1.width / 2) > rect2.x&& rect1.x + (rect1.width / 2) < rect2.x + rect2.width && rect1.y + (rect1.height / 2) > rect2.y&& rect1.y + (rect1.height / 2) < rect2.y + rect2.height)
	{
		return true;
	}
	
	return false;
}



Collisions::~Collisions()
{
	mInstance = NULL;
}
