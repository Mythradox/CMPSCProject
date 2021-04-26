#include <stdbool.h>

#include "defs.h"
#include "structs.h"

extern SDL_Texture* LoadTexture(char *filename);
extern void Draw(Sprite sprite, bool centered);
extern double GetSpriteSin(Sprite sprite);
extern double GetSpriteCos(Sprite sprite);
extern Sprite BoundsCheck(Sprite sprite);
extern Sprite RotationCheck(Sprite sprite);

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
bool isPropelling;
bool isDashing;
bool dashInitiated;
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
	isPropelling = false;
	isDashing = false;
	dashInitiated = false;
}

void ShipUpdate(void)
{
	// Accelerating
	if (input.up)
        {
                double player_sin = GetSpriteSin(player.sprite);
                double player_cos = -GetSpriteCos(player.sprite);
                double dX = player_sin;
                double dY = player_cos;
                dX *= ACCEL;
                dY *= ACCEL;
                if (input.space)
                {
                        dX *= DASH_MULTIPLIER;
                        dY *= DASH_MULTIPLIER;
                }
                player.delta.x += dX;
                player.delta.y += dY;
                shipFire.rotation = player.sprite.rotation;
                shipFire.location.x = player.sprite.location.x - (player_sin * SHIP_RADIUS);
                shipFire.location.y = player.sprite.location.y - (player_cos * SHIP_RADIUS);
		isPropelling = true;
        }
	else
		isPropelling = false;
	// Rotate left
        if (input.left)
                player.sprite.rotation -= ROTATION_INC;
	// Rotate right
        if (input.right)
                player.sprite.rotation += ROTATION_INC;

	// During dash
        if (isDashing)
        {
                if (dashTimer == DASH_PERIOD)
                        dashInitiated = false;
                if (dashTimer > 0)
                        dashTimer--;
                else if (dashTimer == 0)
                {
                        isDashing = false;
                        player.sprite.alpha = 255;
                        dashCooldownTimer = DASH_COOLDOWN;
                }
        }

        if (dashCooldownTimer > 0)
                dashCooldownTimer--;

	// Initiate dash
        if (input.space)
        {
		
		if (dashCooldownTimer == 0 && !isDashing)
		{
                	double player_sin = GetSpriteSin(player.sprite);
                	double player_cos = -GetSpriteCos(player.sprite);
                	double dX = player_sin;
                	double dY = player_cos;
			dX *= DASH_MULTIPLIER;
                	dY *= DASH_MULTIPLIER;
                	player.delta.x += dX;
                	player.delta.y += dY;
                	dashTimer = DASH_PERIOD;
			dashInitiated = true;
			isDashing = true;
			player.sprite.alpha = 128;
		}
        }
	
        player.sprite = BoundsCheck(player.sprite);
        player.sprite = RotationCheck(player.sprite);
        
	if (!isDashing)
		player = ShipVelocityCheck(player);

        player.sprite.location.x += player.delta.x;
        player.sprite.location.y += player.delta.y;
}

void ShipDraw()
{
	Draw(player.sprite, true);
	if (isPropelling)
		Draw(shipFire, true);

}


