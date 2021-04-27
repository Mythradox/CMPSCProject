/*
 * g_main.c
 * 
 * Main game loop
 */

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "structs.h"

extern void SDLInit(void);
extern void ClearBuffer(void);
extern void PresentBuffer(void);
extern void EventInput(void);

extern void ShipInitialize(void);
extern void ShipUpdate(void);
extern void ShipDraw(void);

extern void AsteroidInitialize(void);
extern void AsteroidUpdate(void);
extern void AsteroidDraw(void);

extern void InitializeAudio(void);
extern void ShipSounds(void);

Game game;
Input input;

void MainUpdate(void)
{
	EventInput();
	ShipUpdate();
	AsteroidUpdate();
}

void MainDraw(void)
{
	ShipDraw();
	AsteroidDraw();
}

int main(int argc, char *argv[])
{
	SDLInit();
	InitializeAudio();
	ShipInitialize();
	AsteroidInitialize();
	while (true)
	{
		ClearBuffer();
		MainUpdate();
		MainDraw();
		ShipSounds();
		PresentBuffer();
		SDL_Delay(16);
	}
	return 0;
}
