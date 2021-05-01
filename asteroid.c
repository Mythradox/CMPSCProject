#include <stdio.h>
#include <stdbool.h>

#include "defs.h"
#include "structs.h"
#include "enum.h"

extern SDL_Texture* LoadTexture(char *filename);
extern void Draw(Sprite sprite, bool centered);
extern bool Contains(Sprite a, Sprite b);

extern Entity player;

extern void BoundsCheck(Sprite* sprite);
extern double RotationCheck(double rotation);

const int ASTEROID_MIN_VELOCITY = 1.00;
const int ASTEROID_MAX_VELOCITY = 3.00;
const double ASTEROID_ROTATION_INC = 3.00;

extern enum ShipState shipState;

Entity bigAsteroid;
Entity medAsteroid;
Entity smallAsteroid;

void AsteroidMove(Entity* asteroid)
{
	// Cringe!
	if (asteroid->sprite.alpha != 0)
	{
		asteroid->sprite.rotation += ASTEROID_ROTATION_INC;
		BoundsCheck(&asteroid->sprite);
		RotationCheck(asteroid->sprite.rotation);
		asteroid->sprite.location.x += asteroid->delta.x;
		asteroid->sprite.location.y += asteroid->delta.y;

		if (Contains(player.sprite, asteroid->sprite))
		{
			switch (shipState)
			{
			case DASHING:
				asteroid->sprite.alpha = 0;
				break;
			default:
				if (asteroid->sprite.alpha != 0)
					shipState = DEATH;
				break;
			}
		
		}
	}
}

void AsteroidInitialize(void)
{
	bigAsteroid.sprite.texture = LoadTexture("Resources/Graphics/BigAsteroid.png");
	bigAsteroid.sprite.location.x = 0;
	bigAsteroid.sprite.location.y = 0;
	bigAsteroid.sprite.dimensions.x = 64;
	bigAsteroid.sprite.dimensions.y = 64;
	bigAsteroid.sprite.rotation = 0;
	bigAsteroid.sprite.alpha = 255;
	bigAsteroid.delta.x = 1.00;
	bigAsteroid.delta.y = 1.00;

	medAsteroid.sprite.texture = LoadTexture("Resources/Graphics/MedAsteroid.png");
	medAsteroid.sprite.location.x = 50;
	medAsteroid.sprite.location.y = 50;
	medAsteroid.sprite.dimensions.x = 32;
	medAsteroid.sprite.dimensions.y = 32;
	medAsteroid.sprite.rotation = 0;
	medAsteroid.sprite.alpha = 255;
	medAsteroid.delta.x = 1.50;
	medAsteroid.delta.y = 1.50;

	smallAsteroid.sprite.texture = LoadTexture("Resources/Graphics/SmallAsteroid.png");
	smallAsteroid.sprite.location.x = SCREEN_WIDTH / 3;
	smallAsteroid.sprite.location.y = SCREEN_HEIGHT / 3;
	smallAsteroid.sprite.dimensions.x = 24;
	smallAsteroid.sprite.dimensions.y = 24;
	smallAsteroid.sprite.rotation = 0;
	smallAsteroid.sprite.alpha = 255;
	smallAsteroid.delta.x = 2.00;
	smallAsteroid.delta.y = 2.00;

}

void AsteroidUpdate(void)
{
	AsteroidMove(&bigAsteroid);
	AsteroidMove(&medAsteroid);
	AsteroidMove(&smallAsteroid);
}

void AsteroidDraw(void)
{
	Draw(bigAsteroid.sprite, true);
	Draw(medAsteroid.sprite, true);
	Draw(smallAsteroid.sprite, true);
}
