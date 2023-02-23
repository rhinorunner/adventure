#include <iostream>
#include <thread>

#include <windows.h>
#include <SDL.h>
#undef main

#include "lib.hpp"
#include "render.hpp"

int main() 
{
	uSDL_SETUP();

	SDL_Event event;
	bool looping = true;
	uint16_t mouseX, mouseY;

	Ent ent1 {10,10,100,100};
	ent1.setSprite({});

	while (looping) 
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_MOUSEMOTION) {
			mouseX = event.motion.x;
			mouseY = event.motion.y;
		}
		else if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			// exit
			case SDLK_ESCAPE:
				looping = false;
				uSDL_KILL();
			}
		}


		SDL_RenderPresent(A_RENDERER);
	}

	return 0;
}