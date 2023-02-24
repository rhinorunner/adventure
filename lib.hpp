#ifndef LIB_HPP_CHECK
#define LIB_HPP_CHECK

#include <iostream>
#include <vector>
#include <array>
#include <chrono>
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

typedef std::vector<std::vector<RGB_t>> PixelMap;
typedef std::vector<std::vector<char>> PixelMapChar;

static SDL_Window* A_WINDOW;
static SDL_Renderer* A_RENDERER;

#include "render.hpp"

std::vector<Ent> EntVec {};

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
		{'B','B','b','b','Y','R','Y','R','Y','G'},
		{'B','B','b','b','Y','R','Y','R','Y','G'},
		{'B','B','b','b','Y','R','Y','R','Y','G'},
		{'B','B','b','b','G','G','G','G','G','G'},
		{'B','B','b','b','G','G','G','G','G','G'},
		{'B','b','b','b','C','P','P','W','W','W'},
		{'B','b','b','b','C','P','P','W','W','W'},
		{'B','b','b','b','C','P','P','W','W','W'},
		{'B','b','b','b','C','P','P','W','W','W'},
		{'B','b','b','b','C','P','P','W','W','W'},
	};
}

PixelMap pmcToPm(const PixelMapChar& pmc) {
	PixelMap toReturn {};
	std::vector<RGB_t> temp {};
	for (auto& x : pmc) {
		temp = {};
		for (auto& y : x)
			for (auto& z : pixelMapKey)
				if (z.first == y) temp.push_back(z.second);
		toReturn.push_back(temp);
	}
	return toReturn;
}

class BetterRand {
public:
	// adds this to random each time, optional
	int32_t extraRand;
	BetterRand(const int32_t &ExtraRand = 0) : extraRand(ExtraRand){};
	uint32_t genRand(
		const int32_t &extra = 4, 
		bool resetExtraRand = true, 
		int32_t resetERextraIt = 2
	) {
		if (resetExtraRand)
		  extraRand = genRand(resetERextraIt, false);
		// set random to unix time
		auto cool = std::chrono::system_clock::now();
		auto very =
		    (unsigned int)
			std::chrono::time_point_cast<std::chrono::milliseconds>
			(cool).time_since_epoch().count();
		// add random()
		if (extra >= 1)
			very -= rand();
		// add line number
		if (extra >= 2)
			very += __LINE__;
		// add an iteration (extra = 2)
		if (extra >= 3)
			very += genRand(2, false);
		// bitshift right or left based on another iteration
		if (extra >= 4)
			(genRand(2, false)) % 2 ? very >>= 1 : very <<= 1;
		// subtract an iteration (extra = 4)		
		return (very + extraRand);
	}
};


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