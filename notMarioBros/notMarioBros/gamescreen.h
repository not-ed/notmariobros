#pragma once
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SDL.h>
#include "score.h"

class GameScreen
{
protected:
	SDL_Renderer* renderer;
	// A pointer to the score counter held in the game screen manager - This should NOT be deleted on screen destruction as it is shared!
	ScoreCounter* scoreCounter;
public:
	GameScreen(SDL_Renderer* game_renderer,ScoreCounter* score_counter);
	virtual ~GameScreen();

	virtual void Render() {};
	virtual void Update(float delta_time, SDL_Event e) {};
};

#endif