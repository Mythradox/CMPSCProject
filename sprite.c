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

Sprite RotationCheck(Sprite sprite)
{
        sprite.rotation = sprite.rotation < 0 ? MAX_ROTATION : sprite.rotation;
        sprite.rotation = sprite.rotation > MAX_ROTATION ? 0 : sprite.rotation;
       return sprite;
}

double GetSpriteSin(Sprite sprite)
{
        double spriteSin = sin(sprite.rotation * DEGREES_TO_RADIANS);
        return spriteSin;
}

double GetSpriteCos(Sprite sprite)
{
        double spriteCos = cos(sprite.rotation * DEGREES_TO_RADIANS);
        return spriteCos;
}

