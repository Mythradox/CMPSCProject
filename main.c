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

const double ACCEL = 0.10;
const double ROTATION_INC = 2.00;
const double VELOCITY_MAX = 5.00;
const double DEGREES_TO_RADIANS = (M_PI / 180);
const double TWO_PI = 2 * M_PI;
const double MAX_ROTATION = 360.00;
const int SHIP_RADIUS = 16;
const int MAX_BULLETS = 3;
const int BULLET_LIFETIME = 60;

Game game;
Input input;
Entity player;
Entity bullet;
Sprite shipFire;

Entity shipVelocityCheck(Entity entity)
{
	entity.delta.x = entity.delta.x < -VELOCITY_MAX ? -VELOCITY_MAX : entity.delta.x;
	entity.delta.x = entity.delta.x > VELOCITY_MAX ? VELOCITY_MAX : entity.delta.x;
	entity.delta.y = entity.delta.y < -VELOCITY_MAX ? -VELOCITY_MAX : entity.delta.y;
	entity.delta.y = entity.delta.y > VELOCITY_MAX ? VELOCITY_MAX : entity.delta.y;
	return entity;
}

Sprite boundsCheck(Sprite sprite)
{
	float x_min = -sprite.dimensions.x;
	float x_max = SCREEN_WIDTH + sprite.dimensions.x;
	float y_min = -sprite.dimensions.y;
	float y_max = SCREEN_HEIGHT + sprite.dimensions.y;
	sprite.location.x = sprite.location.x < x_min ? x_max : sprite.location.x;
	sprite.location.x = sprite.location.x > x_max ? x_min : sprite.location.x;
	sprite.location.y = sprite.location.y < y_min ? y_max : sprite.location.y;
	sprite.location.y = sprite.location.y > y_max ? y_min : sprite.location.y;
	return sprite;
}

Sprite rotationCheck(Sprite sprite)
{
	sprite.rotation = sprite.rotation < 0 ? MAX_ROTATION : sprite.rotation;
	sprite.rotation = sprite.rotation > MAX_ROTATION ? 0 : sprite.rotation;
	return sprite;
}

double getSpriteSin(Sprite sprite)
{
	double spriteSin = sin(sprite.rotation * DEGREES_TO_RADIANS);
	return spriteSin;
}

double getSpriteCos(Sprite sprite)
{
	double spriteCos = cos(sprite.rotation * DEGREES_TO_RADIANS);
	return spriteCos;
}

void Update(void)
{
	EventInput();
	if (input.up)
	{
		double player_sin = getSpriteSin(player.sprite);
		double player_cos = -getSpriteCos(player.sprite);
		double dX = player_sin;
		double dY = player_cos;
		dX *= ACCEL;
		dY *= ACCEL;
		player.delta.x += dX;
		player.delta.y += dY;
		shipFire.rotation = player.sprite.rotation;
		shipFire.location.x = player.sprite.location.x - (player_sin * SHIP_RADIUS);
		shipFire.location.y = player.sprite.location.y - (player_cos * SHIP_RADIUS);
	}
	if (input.left)
		player.sprite.rotation -= ROTATION_INC;
	if (input.right)
		player.sprite.rotation += ROTATION_INC;
	/*
	if (input.space)
		fireBullet(player);
	*/

	player.sprite = boundsCheck(player.sprite);
	player.sprite = rotationCheck(player.sprite);
	player = shipVelocityCheck(player);

	player.sprite.location.x += player.delta.x;
	player.sprite.location.y += player.delta.y;

	/*
	if (&bullet != NULL)
	{
		bullet.sprite.x += bullet.delta.x;
		bullet.sprite.y += bullet.delta.y;
		bullet.health--;
		if (bullet.health == 0)
			&bullet == NULL;
	}
	*/
}

int main(int argc, char *argv[])
{
	SDLInit();
	

	player.sprite.texture = LoadTexture("resources/ship.png");
	player.sprite.location.x = 640.0f;
	player.sprite.location.y = 450.0f;
	player.sprite.dimensions.x = 16;
	player.sprite.dimensions.y = 16;
	player.sprite.origin.x = 8;
	player.sprite.origin.y = 8;
	player.sprite.rotation = 0.00;
	player.delta.x = 0;
	player.delta.y = 0;

	shipFire.texture = LoadTexture("resources/ship_fire.png");
	
	while (true)
	{
		ClearBuffer();
		Update();
		Draw(player.sprite, true);
		if (input.up)
			Draw(shipFire, true);
		PresentBuffer();
		SDL_Delay(16);
	}
	return 0;
}
