#include "gamescreen.h"
//#include <SDL.h>

GameScreen::GameScreen(SDL_Renderer* game_renderer,ScoreCounter* score_counter) {
	renderer = game_renderer;
	scoreCounter = score_counter;
}

GameScreen::~GameScreen() {
	// This only needs to be set to null as it would have been holding the renderer PASSED IN when it was constructed.
	renderer = nullptr;

	// Score counter should not be deleted here as it is shared with the game screen manager!
}