/*
 * s_sdl.c
 * 
 * Initializes SDL
 */

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL_mixer.h>

#include "defs.h"
#include "structs.h"

extern void AudioQuit(void);

extern Game game;


void SDLInit(void)
{
	bool success = true;
	int rendererFlags;
	int windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;
	windowFlags = 0;

	// Initialize SDL video
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("ERROR! SDL couldn't initialize: %s\n", SDL_GetError());
		success = false;
	}
	
	// Initialize SDL timer
	if (SDL_Init(SDL_INIT_TIMER) != 0)
	{
		printf("ERROR! SDL couldn't initialize: %s\n", SDL_GetError());
		success = false;
	}

	// Initialize SDL audio
	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		printf("ERROR! SDL couldn't initialize: %s\n", SDL_GetError());
		success = false;
	}

	// Initialize SDL_mixer
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 )
	{
		printf("ERROR! SDL_mixer could not initialize: %s\n", Mix_GetError());
		success = false;
	}

	game.window = SDL_CreateWindow("CMPSC Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	// Initialize window
	if (!game.window)
	{
		printf("ERROR! SDL couldn't initialize: %s\n", SDL_GetError());
		success = false;
	}

	game.renderer = SDL_CreateRenderer(game.window, -1, rendererFlags);

	// Initialize renderer
	if (!game.renderer)
	{
		printf("ERROR! SDL couldn't initialize: %s\n", SDL_GetError());
		success = false;
	}

	if (!success)
		exit(1);
}

void SDLQuit(void)
{
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyWindow(game.window);
	AudioQuit();
	SDL_Quit();
}
