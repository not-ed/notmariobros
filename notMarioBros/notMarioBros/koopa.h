#pragma once
#ifndef KOOPA_H
#define KOOPA_H

#include "character.h"
#include "constants.h"
#include "commons.h"
#include "timer.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);

	void Render();
	void Update(float delta_time, SDL_Event e);

	void TakeDamage();

	void Jump(float force);

	bool GetInjured() { return injured; }

protected:
	// Relevant texture IDs for roaming, stunned and dead states, as well as dedicated sprites for when angry.
	TEXTURE::ID textureRoaming[2] = { TEXTURE::ID::KOOPA,TEXTURE::ID::KOOPA_ANGRY };
	TEXTURE::ID textureStunned[2] = { TEXTURE::ID::KOOPA_STUN, TEXTURE::ID::KOOPA_ANGRY_STUN };
	TEXTURE::ID textureDead[2] = { TEXTURE::ID::KOOPA_DIE, TEXTURE::ID::KOOPA_ANGRY_DIE };

private:

	Timer injuryTimer;
	bool injured;
	void FlipRightWayUp();
	
	bool angry = false;

	void OnKill();

	// Flip movement direction
	void FlipDirection();
};


#endif