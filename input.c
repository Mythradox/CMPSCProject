#include <stdbool.h>
#include <SDL2/SDL.h>
#include "structs.h"

extern void SDLQuit(void);
extern Input input;

void KeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == false)
	{
		switch(event->keysym.scancode)
		{
			case SDL_SCANCODE_UP:
				input.up = true;
				break;
			case SDL_SCANCODE_W:
				input.up = true;
				break;
			case SDL_SCANCODE_LEFT:
				input.left = true;
				break;
			case SDL_SCANCODE_A:
				input.left = true;
				break;
			case SDL_SCANCODE_RIGHT:
				input.right = true;
				break;
			case SDL_SCANCODE_D:
				input.right = true;
				break;
			default:
				break;
		}
	}
}

void KeyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == false)
	{
		switch(event->keysym.scancode)
		{
			case SDL_SCANCODE_UP:
				input.up = false;
				break;
			case SDL_SCANCODE_W:
				input.up = false;
				break;
			case SDL_SCANCODE_LEFT:
				input.left = false;
				break;
			case SDL_SCANCODE_A:
				input.left = false;
				break;
			case SDL_SCANCODE_RIGHT:
				input.right = false;
				break;
			case SDL_SCANCODE_D:
				input.right = false;
				break;
			default:
				break;
		}
	}
}

void EventInput(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				SDLQuit();
				exit(0);
				break;
			case SDL_KEYDOWN:
				KeyDown(&event.key);
				break;
			case SDL_KEYUP:
				KeyUp(&event.key);
				break;
			default:
				break;
		}
	}
}
