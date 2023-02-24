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
	BetterRand rand {__LINE__ + (short)'Z'};

	for (uint16_t i = 0; i < 100; ++i) {
		Ent temp {
			(10),
			(10),
			(rand.genRand() % A_SCREENWIDTH),
			(rand.genRand() % A_SCREENHEIGHT),
			pmcToPm(Sprites::test)
		};
		EntVec.push_back(temp);
	}

	while (looping) 
	{
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT) {
			looping = false;
			uSDL_KILL();
		}
		else if (event.type == SDL_MOUSEMOTION) {
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

		// blit ents
		for (auto x : EntVec) {
			x.blitSprite(A_RENDERER);
		}

		// present render and clear screen
		SDL_RenderPresent(A_RENDERER);
		SDL_SetRenderDrawColor(A_RENDERER, A_BACKCOLOR.R, A_BACKCOLOR.G, A_BACKCOLOR.B, 255);
		SDL_RenderClear(A_RENDERER);
	}

	return 0;
}