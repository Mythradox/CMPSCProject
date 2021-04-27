#include <stdbool.h>

#include "defs.h"
#include "structs.h"
#include "enum.h"

extern SDL_Texture* LoadTexture(char *filename);
extern void Draw(Sprite sprite, bool centered);
extern double GetSpriteSin(double rotation);
extern double GetSpriteCos(double rotation);
extern Sprite BoundsCheck(Sprite sprite);
extern double RotationCheck(double rotation);

extern Input input;

const double ACCEL = 0.10;
const double ROTATION_INC = 3.00;
const double SHIP_VELOCITY_MAX = 6.00;
const double BULLET_VELOCITY = 10.00;
const int SHIP_RADIUS = 16;
const int DASH_PERIOD = 15;
const int DASH_COOLDOWN= 30;
const int DASH_MULTIPLIER = 10;

int dashTimer;
int dashCooldownTimer;
float dashStartX;
float dashStartY;
bool dashInitiated;
enum ShipState state;

Entity player;
Sprite shipFire;

Entity ShipVelocityCheck(Entity entity)
{
        entity.delta.x = entity.delta.x < -SHIP_VELOCITY_MAX ? -SHIP_VELOCITY_MAX : entity.delta.x;
        entity.delta.x = entity.delta.x > SHIP_VELOCITY_MAX ? SHIP_VELOCITY_MAX : entity.delta.x;
        entity.delta.y = entity.delta.y < -SHIP_VELOCITY_MAX ? -SHIP_VELOCITY_MAX : entity.delta.y;
        entity.delta.y = entity.delta.y > SHIP_VELOCITY_MAX ? SHIP_VELOCITY_MAX : entity.delta.y;
        return entity;
}

void ShipInitialize(void)
{
	player.sprite.texture = LoadTexture("resources/ship.png");
        player.sprite.location.x = SCREEN_WIDTH / 2;
        player.sprite.location.y = SCREEN_HEIGHT / 2;
        player.sprite.dimensions.x = 16;
        player.sprite.dimensions.y = 16;
        player.sprite.rotation = 0.00;
        player.sprite.alpha = 255;
        player.delta.x = 0;
        player.delta.y = 0;

        shipFire.texture = LoadTexture("resources/ship_exhaust.png");
        shipFire.dimensions.x = 8;
        shipFire.dimensions.y = 16;
        shipFire.alpha = 255;

	dashTimer = DASH_PERIOD;
	dashCooldownTimer = 0;
	dashInitiated = false;
}

void ShipUpdate(void)
{
	switch (shipState)
	{
		case DASHING:
			if (dashTimer == DASH_PERIOD)
                		dashInitiated = false;
                	if (dashTimer > 0)
                        	dashTimer--;
                	else if (dashTimer == 0)
                	{
				shipState = IDLE;
                        	dashCooldownTimer = DASH_COOLDOWN;
                	}
			break;
		default:
			player = ShipVelocityCheck(player);
			shipState = IDLE;
        		if (input.left)
                		player.sprite.rotation -= ROTATION_INC;
        		if (input.right)
                		player.sprite.rotation += ROTATION_INC;
			if (input.up)
        		{
                		double player_sin = GetSpriteSin(player.sprite.rotation);
                		double player_cos = -GetSpriteCos(player.sprite.rotation);
                		double dX = player_sin;
                		double dY = player_cos;
                		dX *= ACCEL;
                		dY *= ACCEL;
                		player.delta.x += dX;
                		player.delta.y += dY;
                		shipFire.rotation = player.sprite.rotation;
                		shipFire.location.x = player.sprite.location.x - (player_sin * SHIP_RADIUS);
                		shipFire.location.y = player.sprite.location.y - (player_cos * SHIP_RADIUS);
				shipState = PROPELLING;
 			}
			if (input.space)
        		{
				if (dashCooldownTimer == 0)
				{
                			double playerSin = GetSpriteSin(player.sprite.rotation);
                			double playerCos = -GetSpriteCos(player.sprite.rotation);
                			double dX = playerSin;
                			double dY = playerCos;
					dX *= DASH_MULTIPLIER;
                			dY *= DASH_MULTIPLIER;
                			player.delta.x += dX;
                			player.delta.y += dY;
                			dashTimer = DASH_PERIOD;
					dashInitiated = true;
					shipState = DASHING;
					dashStartX = player.sprite.location.x;
					dashStartY = player.sprite.location.y;
				}
        		}	
			break;
	}

        if (dashCooldownTimer > 0)
                dashCooldownTimer--;

        player.sprite = BoundsCheck(player.sprite);
        player.sprite.rotation = RotationCheck(player.sprite.rotation);
        player.sprite.location.x += player.delta.x;
        player.sprite.location.y += player.delta.y;
}

void ShipDraw()
{
	switch (shipState)
	{
		case DASHING: ;
			int afterImageCount = DASH_PERIOD - dashTimer;
			int alphaIncrement = player.sprite.alpha / DASH_PERIOD;
			for (int i = 0; i < afterImageCount; i++)
			{
				Sprite afterImage;
				afterImage.texture = player.sprite.texture;
				afterImage.alpha = alphaIncrement * i;
				afterImage.rotation = player.sprite.rotation;
				afterImage.location.x = dashStartX + (player.delta.x * i);
				afterImage.location.y = dashStartY + (player.delta.y * i);
				Draw(afterImage, true);
			}
			break;
		case PROPELLING:
			Draw(shipFire, true);
			break;
		default:
			break;
	}
	Draw(player.sprite, true);
}


