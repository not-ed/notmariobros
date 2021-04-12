#pragma once
#ifndef ICICLE_H
#define ICICLE_H

#include "koopa.h"
#include "coin.h"

class CharacterIcicle : public CharacterKoopa
{
public:
	CharacterIcicle(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, FACING start_facing);

	void Update(float delta_time, SDL_Event e);
	
	int GetCoinDropAmount() { return coinDropAmount; }

	// Generate a coin object and return its pointer to the object requesting it
	Coin* DropCoin();
private:
	void OnKill();

	// How many coins to drop if killed by the player or POW block
	int coinDropAmount = 5;
};

#endif