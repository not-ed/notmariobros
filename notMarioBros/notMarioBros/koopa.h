#pragma once
#ifndef KOOPA_H
#define KOOPA_H

#include "character.h"
#include "constants.h"
#include "commons.h"
#include "soundmanager.h"
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

private:
	
	/*float m_single_sprite_w;
	float m_single_sprite_h;*/


	Timer injuryTimer;
	bool m_injured;
	void FlipRightWayUp();
	
	/*float m_injured_time;*/
	

	void OnKill();
	void FlipDirection();

	/*int currentAnimFrame = 0;
	float animSpeed = 0.1f;
	float animTime = 0.0f;*/

};


#endif