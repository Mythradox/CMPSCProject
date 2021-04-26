/*
 * d_draw.c
 * 
 * Handles drawing code
 */

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "structs.h"

extern Game game;

SDL_Texture* LoadTexture(char *filename)
{
	SDL_Texture *texture;
	texture = IMG_LoadTexture(game.renderer, filename);
	return texture;
}

void Draw(Sprite sprite, bool centered)
{
	SDL_Rect rect;
	rect.x = sprite.location.x;
	rect.y = sprite.location.y;
	rect.w = sprite.dimensions.x;
	rect.h = sprite.dimensions.y;
	SDL_QueryTexture(sprite.texture, NULL, NULL, &rect.w, &rect.h);
	if (centered)
	{
		rect.x -= (rect.w / 2);
		rect.y -= (rect.h / 2);
	}
	SDL_SetTextureAlphaMod(sprite.texture, sprite.alpha);
	SDL_RenderCopyEx(game.renderer, sprite.texture, NULL, &rect, sprite.rotation, NULL, 0);
}

void ClearBuffer(void)
{
	SDL_RenderClear(game.renderer);
}
void PresentBuffer(void)
{
	SDL_RenderPresent(game.renderer);
}
