#pragma once
#ifndef COIN_H
#define COIN_H

#include "character.h"
#include "timer.h"

class Coin : public Character
{
public:
	Coin(SDL_Renderer* game_renderer, Vector2D start_position, LevelMap* map);
	~Coin();

	void Update(float delta_time, SDL_Event e);
	void Render();
	bool Expired() { return lifetimeTimer.IsExpired(); }
private:
	Timer lifetimeTimer;
};



#endif