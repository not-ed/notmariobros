#pragma once
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SDL.h>

class GameScreen
{
protected:
	SDL_Renderer* renderer;
public:
	GameScreen(SDL_Renderer* game_renderer);
	virtual ~GameScreen();

	virtual void Render() {};
	virtual void Update(float delta_time, SDL_Event e) {};
};

#endif