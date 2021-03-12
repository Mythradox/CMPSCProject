/*
 * g_main.c
 * 
 * Main game loop
 */

#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "defs.h"

extern SDL_Texture* LoadTexture(char *filename);
extern void SDLInit(void);
extern void Draw(Sprite sprite, bool centered);
extern void ClearBuffer(void);
extern void PresentBuffer(void);
extern void EventInput(void);

Game game;
Player player;
Input input;

int main(int argc, char *argv[])
{
	bool inputHeld = false;
	SDLInit();
	player.sprite.texture = LoadTexture("resources/ship.png");
	player.sprite.location.x = 100.0f;
	player.sprite.location.y = 100.0f;
	player.sprite.dimensions.x = 64;
	player.sprite.dimensions.y = 64;
	player.dX = 0;
	player.dY = 0;

	while (true)
	{
		ClearBuffer();
		EventInput();
		if (input.up | input.left | input.right)
			inputHeld = true;
		if (input.up)
		{
			player.dX += 1.00f;
			player.dY += 1.00f;
		}

		if (player.sprite.location.x >= SCREEN_WIDTH + player.sprite.dimensions.x)
			player.sprite.location.x = 0 - player.sprite.dimensions.x;
		if (player.sprite.location.y >= SCREEN_HEIGHT + player.sprite.dimensions.y)
			player.sprite.location.y = 0 - player.sprite.dimensions.y;
		player.dX -= 0.1f;
		player.dY -= 0.1f;
		player.dX = player.dX < 0 ? 0 : player.dX;
		player.dY = player.dY < 0 ? 0 : player.dY;
		player.sprite.location.x += player.dX;
		player.sprite.location.y += player.dY;
		
		Draw(player.sprite, true);
		PresentBuffer();
		SDL_Delay(16);

	}
	return 0;
}
