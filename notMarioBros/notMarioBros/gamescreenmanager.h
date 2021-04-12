#pragma once
#ifndef GAMESCREENMANAGER_H
#define GAMESCREENMANAGER_H

#include <SDL.h>
#include "commons.h"
#include "score.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* game_renderer, SCREENS starting_screen);
	~GameScreenManager();

	void Render();
	void Update(float delta_time, SDL_Event e);

	// Get rid of the current screen if it exists and create a new one based on what is passed through
	void ChangeScreen(SCREENS new_screen);

private:
	SDL_Renderer* renderer;

	GameScreen* currentScreen;

	ScoreCounter score;
};

#endif