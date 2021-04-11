#pragma once
#ifndef ICICLE_H
#define ICICLE_H

#include "koopa.h"
#include "coin.h"

class CharacterIcicle : public CharacterKoopa
{
public:
	CharacterIcicle(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);

	void Update(float delta_time, SDL_Event e);

	// Generate a coin object and return its pointer.
	int GetCoinDropAmount() { return coinDropAmount; }
	Coin* DropCoin();
private:
	void OnKill();

	// How many coins to drop if killed by the player or POW block
	int coinDropAmount = 5;
};

#endif