#include <stdbool.h>
#include <math.h>

#include "structs.h"
#include "defs.h"

const double DEGREES_TO_RADIANS = (M_PI / 180);
const double TWO_PI = 2 * M_PI;
const double MAX_ROTATION = 360.00;

Sprite BoundsCheck(Sprite sprite)
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

double RotationCheck(double rotation)
{
	double newRotation = rotation;
	newRotation = newRotation < 0 ? MAX_ROTATION : newRotation;
	newRotation = newRotation > MAX_ROTATION ? 0 : newRotation;
	return newRotation;
}

bool Contains(Sprite a, Sprite b)
{
	bool xContact = false;
	bool yContact = false;
	bool contact = false;
	int halfAX = a.dimensions.x / 2;
	int halfAY = a.dimensions.y / 2;
	int halfBX = b.dimensions.x / 2;
	int halfBY = b.dimensions.y / 2;
	if (a.location.x - halfAX >= b.location.x - halfBX && a.location.x + halfAX <= b.location.x + halfBX)
		xContact = true;
	if (a.location.y - halfAY >= b.location.y - halfBY && a.location.y + halfAY <= b.location.y + halfBY)
		yContact = true;
	contact = xContact & yContact;
	return  contact;
}

double GetSpriteSin(double rotation)
{
        double spriteSin = sin(rotation * DEGREES_TO_RADIANS);
        return spriteSin;
}

double GetSpriteCos(double rotation)
{
        double spriteCos = cos(rotation * DEGREES_TO_RADIANS);
        return spriteCos;
}

