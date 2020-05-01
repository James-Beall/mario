#include "Texture2D.h"
#include<SDL_image.h>
#include <iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mTexture = NULL;

	int mWidth = 0;
	int mHeight = 0; 
}

bool Texture2D::LoadFromFile(string path)
{
	//Remove the memory used for a previous texture.
	//FreeTexture();

	//SDL_Texture* mTexture = NULL;
	mTexture = NULL;

	//Load the image.
	SDL_Surface* pSurface = IMG_Load(path.c_str());

	//Set the dimensions.
	mWidth = pSurface->w;
	mHeight = pSurface->h;

	if (pSurface != NULL)
	{
		//Create the texture from the pixels onthe surface.
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);

		//Colour key the image - The colour to be transparent.
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));
		
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		//Remove the loaded surface now that we have the texture.
		SDL_FreeSurface(pSurface);
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}
	return mTexture;
}

void Texture2D::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	//Clear the screen.
	//SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderClear(mRenderer);

	//Set where to render the texture.
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	//Render to screen.
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);

	//Update the screen.
	SDL_RenderPresent(mRenderer);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	//Render to screen.
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}

Texture2D::~Texture2D()
{
	//Free up the memory.
	Free();
	mRenderer = NULL;
}