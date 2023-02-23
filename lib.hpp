#ifndef LIB_HPP_CHECK
#define LIB_HPP_CHECK

#include <iostream>
#include <vector>
#include <SDL.h>

#pragma pack(1)

struct RGB_t {
	uint8_t R;
	uint8_t G;
	uint8_t B;
};

struct RGBI_t {
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t I;
};

/************************************************/

// screen width
static constexpr uint16_t A_SCREENWIDTH = 600;
// screen height
static constexpr uint16_t A_SCREENHEIGHT = 600;
// background color
static constexpr RGB_t A_BACKCOLOR {0,0,0};

/************************************************/

static SDL_Window* A_WINDOW;
static SDL_Renderer* A_RENDERER;

typedef std::vector<std::vector<RGB_t>> PixelMap;
typedef std::vector<std::vector<char>> PixelMapChar;

namespace Colors
{
	RGB_t white  = {255,255,255};
	RGB_t black  = {0  ,0  ,0  };
	RGB_t red    = {255,0  ,0  };
	RGB_t green  = {0  ,255,0  };
	RGB_t blue   = {0  ,0  ,255};
	RGB_t yellow = {255,255,0  };
	RGB_t purple = {255,0  ,255};
	RGB_t cyan   = {0  ,255,255};

	std::array<RGB_t, 8> allColors = {
		white,black,red,green,blue,yellow,purple,cyan
	};

	std::array<RGB_t, 8> list = {
		white,red,green,blue,yellow,purple,cyan
	};
};

std::vector<std::pair<char,RGB_t>> pixelMapKey {
	{'W', Colors::white },
	{'R', Colors::red   },
	{'G', Colors::green },
	{'B', Colors::blue  },
	{'P', Colors::purple},
	{'C', Colors::cyan  },
	{'Y', Colors::yellow},
	{'b', Colors::black }
};

namespace Sprites 
{
	PixelMapChar test = {
		{'W','W','G','G','G'},
		{'W','W','G','G','G'},
		{'W','W','R','R','R'},
		{'W','W','R','R','R'},
		{'W','W','R','R','R'}
	};
}

PixelMap pmcToPm(const PixelMapChar& pmc) {
	PixelMap toReturn {};
	for (auto& x : pmc) 
		for (auto& y : x) 
			for (auto& z : pixelMapKey)
				if (z.first == y) toReturn.push_back(z.second);
}


void uSDL_SETUP()
{
	A_WINDOW = NULL;
	// renderer
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	SDL_CreateWindowAndRenderer(A_SCREENWIDTH, A_SCREENHEIGHT, 0, &A_WINDOW, &A_RENDERER);
	if (A_WINDOW == NULL) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	// set background color
	SDL_SetRenderDrawColor(A_RENDERER, A_BACKCOLOR.R, A_BACKCOLOR.G, A_BACKCOLOR.B, 255);
	SDL_RenderClear(A_RENDERER);
}

void uSDL_KILL() {
	SDL_DestroyWindow(A_WINDOW);
	SDL_Quit();
	exit(0);
}

#endif