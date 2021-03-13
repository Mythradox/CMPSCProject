/*
 * s_structs.h
 *
 * General program structs
 */

#include <SDL2/SDL.h>

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window *window;
} Game;

typedef struct
{
	int up;
	int right;
	int left;
	int space;
} Input;

typedef struct
{
	float x;
	float y;
} Vector2;

typedef struct
{
	SDL_Texture *texture;
	SDL_Rect rect;
	Vector2 location;
	Vector2 dimensions;
	Vector2 origin;
	double rotation;
} Sprite;

typedef struct
{
	Sprite sprite;
	Vector2 delta;
} Entity;

typedef struct
{
	Entity entity;
} Player;

typedef struct
{
	int lifetime;
} Bullet;
