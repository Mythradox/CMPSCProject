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

extern void InitializeAudio(void);
extern void ShipSounds(void);

Game game;
Input input;

void Update(void)
{
	EventInput();
	ShipUpdate();
}

int main(int argc, char *argv[])
{
	SDLInit();
	InitializeAudio();
	ShipInitialize();
	
	while (true)
	{
		ClearBuffer();
		Update();
		ShipDraw();
		ShipSounds();
		PresentBuffer();
		SDL_Delay(16);
	}
	return 0;
}
