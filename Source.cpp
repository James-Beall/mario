#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Constants.h"
#include "Texture2D.h"
#include "GameScreenManager.h"
//#include "Commons.h"
using namespace std;

//Globals
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;
Mix_Music* gMusic = NULL;
//SDL_Texture* gTexture = NULL;

//Function Prototypes
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();
void LoadMusic(string path);
//Texture2D* gTexture = NULL;

void Render()
{
//Clear the screen.
SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
SDL_RenderClear(gRenderer);

//gTexture->Render(Vector2D(), SDL_FLIP_NONE);

//Set where to render the texture.
//SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

//Render to screen.
gameScreenManager->Render();
//SDL_RenderCopyEx(gRenderer, /*gTexture*/ NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

//Update the screen.
SDL_RenderPresent(gRenderer);
}

SDL_Texture* LoadTextureFromFile(string path)
{
	//Remove the memory used for a previous texture.
	FreeTexture();

	SDL_Texture* pTexture = NULL;

	//Load the image.
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		//Create the texture from the pixels onthe surface.
		pTexture = SDL_CreateTextureFromSurface(gRenderer, pSurface);
		if (pTexture == NULL)
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
	return pTexture;
}

void FreeTexture()
{
	/*Check if the texture exists before removing it.
	if (gTexture != NULL)
	{
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
	}*/
}

void LoadMusic(string path)
{
	gMusic = Mix_LoadMUS(path.c_str());
	if (gMusic == NULL)
	{
		std::cout << "Failed to load background music! Error: " << Mix_GetError() << std::endl;
	}
}

bool Update()
{
	//Get the new time.
	Uint32 newTime = SDL_GetTicks();

	//Event Handler
	SDL_Event e;

	//Get the events.
	SDL_PollEvent(&e);

	//Handle any events
	switch (e.type)
	{
		//Click the 'X' to quit.
	case SDL_QUIT:
		return true;
	break;
	}
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;
	return false;
}

bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//All good, so attempt to create the window.
		gWindow = SDL_CreateWindow("Games Engine Creation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		//Load the background texture.
		//gTexture = new Texture2D(gRenderer);
		//if (!gTexture->LoadFromFile("Images/test.bmp"))
		//{
		//	return false;
		//}

		//Initialise the Mixer.
		if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "Mixer could not initialise. Error: " << Mix_GetError();
			return false;
		}

		if (gRenderer != NULL)
		{
			//Initialise PNG Loading.
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not intialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Render could not intialise. Error: " << SDL_GetError();
			return false;
		}

		//Did the window get created?
		if (gWindow == NULL)
		{
			//Nope.
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		return true;
	}
}
void CloseSDL()
{
	//Destroy the game screen manager.
	delete gameScreenManager;
	gameScreenManager = NULL;

	//Clear up the texture.
	FreeTexture();

	//Release the texture.
	//delete gTexture;
	//gTexture = NULL;

	//Release the music.
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//Release the renderer.
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	//Release the window.
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems.
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Check if SDL was set up correctly.
	if (InitSDL())
	{
		//Set up the game screen manager - Start with Level 1.
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
		gOldTime = SDL_GetTicks();
		LoadMusic("Music/Mario.mp3");
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(gMusic, -1);
		}

		//Flag to check if we wish to quit.
		bool quit = false;

		//Game Loop.
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}
	//Close Window and free resources.
	CloseSDL();

	return 0;
}