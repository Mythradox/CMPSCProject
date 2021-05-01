#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL_mixer.h>

#include "structs.h"
#include "enum.h"

extern enum ShipState shipState;
extern bool dashInitiated;

Mix_Chunk* shipDash;
Mix_Chunk* shipHum;
Mix_Chunk* asteroidHit;

void InitializeAudio()
{
	shipDash = Mix_LoadWAV("Resources/Audio/ShipDash.wav");
	shipHum = Mix_LoadWAV("Resources/Audio/ShipHum.wav");
	asteroidHit = Mix_LoadWAV("Resources/Audio/AsteroidHit.wav");
}

void ShipSounds()
{
	if (dashInitiated)
		Mix_PlayChannel(-1, shipDash, 0);
	switch (shipState)
	{
		case PROPELLING:
			Mix_PlayChannel(-1, shipHum, 0);
		default:
			break;
	}
}

void AudioQuit()
{
	Mix_FreeChunk(shipDash);
	Mix_FreeChunk(asteroidHit);
	Mix_FreeChunk(shipHum);
	Mix_Quit();
}
