#ifndef RENDER_HPP_CHECK
#define RENDER_HPP_CHECK

#include <iostream>
#include <vector>
#include <array>
#include <SDL.h>
#include "lib.hpp"

float distance(
	const std::pair<uint16_t, uint16_t>& coords1,
	const std::pair<uint16_t, uint16_t>& coords2
) {
	return (float)sqrt(
		pow(coords1.first - coords2.first, 2) +
		pow(coords1.second - coords2.second, 2)
	);
}

class uRenderer_t {
private:
	SDL_Window* Window;
	SDL_Renderer* Renderer;

public:
	uRenderer_t(SDL_Window* window, SDL_Renderer* renderer)
		: Window(window), Renderer(renderer) {}

	// blit a pixel
	void blitPixel(
		const uint16_t& X,
		const uint16_t& Y,
		const RGB_t& color
	) {
		SDL_SetRenderDrawColor(Renderer, color.R, color.G, color.B, 255);
		SDL_RenderDrawPoint(Renderer, X, Y);
	}

	// blit a line from coords1 to coords2
	void blitLine(
		const std::pair<uint16_t, uint16_t>& coords1,
		const std::pair<uint16_t, uint16_t>& coords2,
		const RGB_t& color,
		uint16_t thickness = 1
	) {
		SDL_SetRenderDrawColor(
			Renderer,
			color.R,
			color.G,
			color.B,
			255
		);
		for (uint16_t i = 0; i < thickness; ++i) {
			SDL_RenderDrawLine(
				Renderer,
				coords1.first + i,
				coords1.second + i,
				coords2.first + i,
				coords2.second + i
			);
		}
	}

	// blit a circle
	void blitCircle(
		const uint16_t& centerX,
		const uint16_t& centerY,
		const uint16_t& radius,
		const RGB_t& color
	) {
		const int32_t diameter = (radius * 2);

		int16_t x = (radius - 1);
		int16_t y = 0, tx = 1, ty = 1;
		int16_t error = (tx - diameter);

		SDL_SetRenderDrawColor(Renderer, color.R, color.G, color.B, 255);

		while (x >= y) 
		{
			// each of the following renders an octant of the circle
			SDL_RenderDrawPoint(Renderer, centerX + x, centerY - y);
			SDL_RenderDrawPoint(Renderer, centerX + x, centerY + y);
			SDL_RenderDrawPoint(Renderer, centerX - x, centerY - y);
			SDL_RenderDrawPoint(Renderer, centerX - x, centerY + y);
			SDL_RenderDrawPoint(Renderer, centerX + y, centerY - x);
			SDL_RenderDrawPoint(Renderer, centerX + y, centerY + x);
			SDL_RenderDrawPoint(Renderer, centerX - y, centerY - x);
			SDL_RenderDrawPoint(Renderer, centerX - y, centerY + x);

			if (error <= 0) {
				++y;
				error += ty;
				ty += 2;
			}
			if (error > 0) {
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}
	}
};

class Ent {
public: 
	uint16_t Width, Height, X, Y, ID;
	float Velocity, Angle;
	PixelMap Sprite {};

	Ent(
		const uint16_t& width,
		const uint16_t& height,
		const uint16_t& x,
		const uint16_t& y,
		const float& angle,
		const float& velocity,
		const uint16_t& id,
		PixelMap pmap = {}
	) : 
		Width(width),
		Height(height),
		X(x),
		Y(y),
		Angle(angle),
		Velocity(velocity),
		ID(id),
		Sprite(pmap)
	{}

	// check if ent is colliding with another ent
	bool isColliding(Ent& other) {
		if (
			   X < (other.X + other.Width)
			&& (X + Width) > other.X
			&& Y < (other.Y + other.Height)
			&& (Y + Height) > other.Y
			) return true;
		
		return false;
	}
	
	// blit the sprite
	void blitSprite(SDL_Renderer* renderer) {
		for (uint16_t i = 0; i < Sprite.size(); ++i) {
			for (uint16_t l = 0; l < Sprite[i].size(); ++l) {
				SDL_SetRenderDrawColor(
					renderer,
					Sprite[i][l].R,
					Sprite[i][l].G,
					Sprite[i][l].B,
					255
				);
				SDL_RenderDrawPoint(renderer, X+l, Y+i);
			}
		}
	}
	
	// blit the sprite
	// uRenderer_t overload
	void blitSprite(uRenderer_t renderer) {
		for (uint16_t i = 0; i < Sprite.size(); ++i) {
			for (uint16_t l = 0; l < Sprite[i].size(); ++l) {
				renderer.blitPixel(X+l, Y+l, Sprite[i][l]);
			}
		}
	}
};

#endif