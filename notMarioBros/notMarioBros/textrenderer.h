#pragma once
#ifndef TEXTURERENDERER_H
#define TEXTURERENDERER_H

#include <SDL.h>
#include "commons.h"
#include <string>
#include "texture2d.h"

// The size of any given letter in a font sprite sheet.
#define CHARACTER_WIDTH 16
#define CHARACTER_HEIGHT 16
// How many characters are on each row of a font sprite sheet.
#define CHARACTER_ROW_COUNT 12

namespace FONT {
	enum ID
	{
		REGULAR,
		MARIO,
		LUIGI,
		GOLD,
		SILVER,
		count
	};

	enum ALLIGNMENT {
		LEFT,
		CENTER,
		RIGHT
	};
}

namespace Text {
	void Initialize(SDL_Renderer* renderer);
	void Shutdown();
	void Draw(std::string text, IntVector2D position, FONT::ID font, FONT::ALLIGNMENT allignment);
}

static bool initialized;
static SDL_Renderer* renderer;
static Texture2D* fonts[FONT::ID::count];

#endif