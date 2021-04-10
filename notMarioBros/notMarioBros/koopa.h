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
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void TakeDamage();
	void Jump(float force);

	bool GetInjured() { return m_injured; }

protected:
	TEXTURE::ID textureRoaming[2] = { TEXTURE::ID::KOOPA,TEXTURE::ID::KOOPA_ANGRY };
	TEXTURE::ID textureStunned[2] = { TEXTURE::ID::KOOPA_STUN, TEXTURE::ID::KOOPA_ANGRY_STUN };
	TEXTURE::ID textureDead[2] = { TEXTURE::ID::KOOPA_DIE, TEXTURE::ID::KOOPA_ANGRY_DIE };

private:
	
	/*float m_single_sprite_w;
	float m_single_sprite_h;*/


	Timer injuryTimer;
	bool m_injured;
	void FlipRightWayUp();
	
	/*float m_injured_time;*/
	
	bool angry = false;

	void OnKill();
	void FlipDirection();


	

};


#endif