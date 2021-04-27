#include <stdio.h>
#include <stdbool.h>

#include "defs.h"
#include "structs.h"
#include "enum.h"

extern SDL_Texture* LoadTexture(char *filename);
extern void Draw(Sprite sprite, bool centered);
extern bool Contains(Sprite a, Sprite b);

extern Entity player;

extern double GetSpriteSin(double rotation);
extern double GetSpriteCos(double rotation);
extern Sprite BoundsCheck(Sprite sprite);
extern double RotationCheck(double rotation);

const int ASTEROID_MIN_VELOCITY = 1.00;
const int ASTEROID_MAX_VELOCITY = 3.00;
const double ASTEROID_ROTATION_INC = 3.00;

enum ShipState shipState;
Entity asteroid;

void AsteroidInitialize(void)
{
	asteroid.sprite.texture = LoadTexture("resources/meteor.png");
	asteroid.sprite.location.x = SCREEN_WIDTH / 4;
	asteroid.sprite.location.y = SCREEN_HEIGHT / 2;
	asteroid.sprite.dimensions.x = 64;
	asteroid.sprite.dimensions.y = 64;
	asteroid.sprite.rotation = 0;
	asteroid.sprite.alpha = 255;
	asteroid.delta.x = 1.00;
	asteroid.delta.y = 1.00;
}

void AsteroidUpdate(void)
{
	asteroid.sprite.rotation += ASTEROID_ROTATION_INC;
	asteroid.sprite = BoundsCheck(asteroid.sprite);
	RotationCheck(asteroid.sprite.rotation);
	asteroid.sprite.location.x += asteroid.delta.x;
	asteroid.sprite.location.y += asteroid.delta.y;
	if (Contains(asteroid.sprite, player.sprite))
	{
		printf("YES!!!!");
		switch (shipState)
		{
		case DASHING:
			asteroid.sprite.alpha = 128;	
			break;
		default:
			break;
		}
	}
			
}

void AsteroidDraw(void)
{
	Draw(asteroid.sprite, true);
}
