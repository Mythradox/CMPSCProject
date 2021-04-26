#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL_mixer.h>

#include "structs.h"

extern bool dashInitiated;

Mix_Chunk* shipDash;

void InitializeAudio()
{
	shipDash = Mix_LoadWAV("resources/shipDash.wav");
	if (shipDash == NULL)
		printf(Mix_GetError());
}

void ShipSounds()
{
	if (dashInitiated)
		Mix_PlayChannel(-1, shipDash, 0);
}

void AudioQuit()
{
	Mix_FreeChunk(shipDash);
	shipDash = NULL;
	Mix_Quit();
}
