#pragma once
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H
#include "SDL.h"
#include "Commons.h"
#include <iostream>

class Texture2D
{
public:
	//Public Function Prototypes
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	void Free();
	bool LoadFromFile(std::string path);
	void Render(Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f);
	void Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle = 0.0f);

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
private:
	//Private Variables
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;

	int mWidth = 0;
	int mHeight = 0;
};






#endif //_TEXTURE2D_H