#pragma once
#ifndef KOOPA_H
#define KOOPA_H

#include "character.h"
#include "constants.h"
#include "commons.h"
#include "timer.h"

// An identifier of the explicit enemy type, as this detail can be lost in derived classes from CharacterKoopa
enum ENEMY_TYPE {
	KOOPA,
	CRAB,
	ICICLE,
	FIREBALL
};

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, FACING start_facing);
	~CharacterKoopa();
	void Render();
	void Update(float delta_time, SDL_Event e);

	void TakeDamage();

	void Jump(float force);

	// Return the explicit type of enemy, the details of which might otherwise be lost when casting to derived classes through the base one (Like through a game screen).
	ENEMY_TYPE GetEnemyType() { return type; }

	bool GetInjured() { return injured; }

protected:
	// Relevant texture IDs for roaming, stunned and dead states, as well as dedicated sprites for when angry.
	TEXTURE::ID textureRoaming[2] = { TEXTURE::ID::KOOPA,TEXTURE::ID::KOOPA_ANGRY };
	TEXTURE::ID textureStunned[2] = { TEXTURE::ID::KOOPA_STUN, TEXTURE::ID::KOOPA_ANGRY_STUN };
	TEXTURE::ID textureDead[2] = { TEXTURE::ID::KOOPA_DIE, TEXTURE::ID::KOOPA_ANGRY_DIE };
	bool angry = false;

	float regularMovementSpeed = KOOPA_SPEED;
	float angryMovementSpeed = KOOPA_ANGRY_SPEED;

protected:

	Timer injuryTimer;
	bool injured;
	void FlipRightWayUp();

	void OnKill();

	// Flip movement direction
	void FlipDirection();
	
	// Explicit identifier of an enemies type when its potentially derived nature is not known.
	ENEMY_TYPE type = ENEMY_TYPE::KOOPA;
};


#endif