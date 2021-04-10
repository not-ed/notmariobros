#include "gamescreen.h"
#include <SDL.h>

GameScreen::GameScreen(SDL_Renderer* game_renderer) {
	renderer = game_renderer;
}

GameScreen::~GameScreen() {
	// This only needs to be set to null as it would have been holding the renderer PASSED IN when it was constructed.
	renderer = nullptr;
}