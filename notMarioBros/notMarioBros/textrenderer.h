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

	// Text-alignment
	enum ALLIGNMENT {
		LEFT,
		CENTER,
		RIGHT
	};
}

namespace Text {
	// Startup/shutdown
	void Initialize(SDL_Renderer* renderer);
	void Shutdown();

	// Draw a specified string of text at a given position, font, and text allignment
	void Draw(std::string text, IntVector2D position, FONT::ID font, FONT::ALLIGNMENT allignment);
}

// If the singleton object has already been initialized.
static bool initialized;

static SDL_Renderer* renderer;

static Texture2D* fonts[FONT::ID::count];

#endif