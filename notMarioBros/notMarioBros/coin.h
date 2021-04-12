#pragma once
#ifndef COIN_H
#define COIN_H

#include "character.h"
#include "timer.h"

class Coin : public Character
{
public:
	Coin(SDL_Renderer* game_renderer, Vector2D start_position, LevelMap* map);

	void Update(float delta_time, SDL_Event e);
	void Render();

	// Has the coin run out of time to be picked up?
	bool Expired() { return lifetimeTimer.IsExpired(); }
private:
	// How long the coin has to be picked up before vanishing
	Timer lifetimeTimer;
};

#endif