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

const double ACCEL = 0.33;
const double ROTATION_INC = 2.00;
const double VELOCITY_MAX = 3.00;
const double DEGREES_TO_RADIANS = (M_PI / 180);
const double TWO_PI = 2 * M_PI;

Game game;
Player player;
Input input;

void Update(void)
{
	bool inputHeld = false;
	EventInput();
	if (input.up | input.left | input.right)
		inputHeld = true;
	if (input.up)
	{
		double deltaX = sin(player.sprite.rotation * DEGREES_TO_RADIANS);
		double deltaY = -cos(player.sprite.rotation * DEGREES_TO_RADIANS);
		deltaX *= ACCEL;
		deltaY *= ACCEL;
		player.dX += deltaX;
		player.dY += deltaY;
	}
	if (input.left)
		player.sprite.rotation -= ROTATION_INC;
	if (input.right)
		player.sprite.rotation += ROTATION_INC;

	player.sprite.location.x = player.sprite.location.x < -player.sprite.dimensions.x ? SCREEN_WIDTH + player.sprite.dimensions.x : player.sprite.location.x;
	player.sprite.location.x = player.sprite.location.x > SCREEN_WIDTH + player.sprite.dimensions.x ? -player.sprite.dimensions.x : player.sprite.location.x;
	player.sprite.location.y = player.sprite.location.y < -player.sprite.dimensions.y ? SCREEN_HEIGHT + player.sprite.dimensions.y : player.sprite.location.y;
	player.sprite.location.y = player.sprite.location.y > SCREEN_HEIGHT + player.sprite.dimensions.y ? -player.sprite.dimensions.y : player.sprite.location.y;

	player.dX = player.dX < -VELOCITY_MAX ? -VELOCITY_MAX : player.dX;
	player.dX = player.dX > VELOCITY_MAX ? VELOCITY_MAX : player.dX;
	player.dY = player.dY < -VELOCITY_MAX ? -VELOCITY_MAX : player.dY;
	player.dY = player.dY > VELOCITY_MAX ? VELOCITY_MAX : player.dY;

	player.sprite.rotation = player.sprite.rotation < 0 ? 360.0 : player.sprite.rotation;
	player.sprite.rotation = player.sprite.rotation > 360.0 ? 0 : player.sprite.rotation;
	player.sprite.location.x += player.dX;
	player.sprite.location.y += player.dY;
}

int main(int argc, char *argv[])
{
	SDLInit();
	player.sprite.texture = LoadTexture("resources/ship.png");
	player.sprite.location.x = 100.0f;
	player.sprite.location.y = 100.0f;
	player.sprite.dimensions.x = 64;
	player.sprite.dimensions.y = 64;
	player.sprite.origin.x = 16;
	player.sprite.origin.y = 16;
	player.dX = 0;
	player.dY = 0;
	player.sprite.rotation = 0.00;
	while (true)
	{
		ClearBuffer();
		Update();
		Draw(player.sprite, true);
		PresentBuffer();
		SDL_Delay(16);
		printf("%.3f %s\n", player.sprite.rotation);
	}
	return 0;
}
