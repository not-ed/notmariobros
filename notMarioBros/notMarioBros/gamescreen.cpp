#include "gamescreen.h"
#include <SDL.h>

GameScreen::GameScreen(SDL_Renderer* renderer) {
	m_renderer = renderer;
}

GameScreen::~GameScreen() {
	// This only needs to be set to null as it would have been holding the renderer PASSED IN when it was constructed.
	m_renderer = nullptr;
}

void GameScreen::Render() {

}

void GameScreen::Update(float deltaTime, SDL_Event e) {

}