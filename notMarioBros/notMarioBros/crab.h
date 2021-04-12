#pragma once
#ifndef CRAB_H
#define CRAB_H

#include "koopa.h"
#include "fireball.h"
#include <vector>

class CharacterCrab : public CharacterKoopa
{
public:
	CharacterCrab(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, FACING start_facing);
	~CharacterCrab();

	// Are any fireballs being held by the crab object that need to be handed over?
	bool HoldingFireballs() { return (heldFireballs.size() > 0); }
	// Hand over a held pointer, if any to a held fireball, removing it from the heldFireballs vector to be managed by the caller (ideally a game screen).
	FireBall* FetchFireball();

	void Update(float delta_time, SDL_Event e);

private:
	void CreateFireballs();

	// Fireballs that have been spawned, but not yet held by the current game screen for management.
	std::vector<FireBall*> heldFireballs;

	// Fireball texture IDs to use when spawning fire balls when neutral or angry
	TEXTURE::ID fireballTexture[2]{ TEXTURE::ID::FIREBALL, TEXTURE::ID::FIREBALL_RED };

	// Fireball spawn rates
	Timer fireballSpawnTimer;
	float fireballSpawnFrequency = 2.5f;
	float fireballSpawnFrequencyAngry = 1.15f;
};


#endif