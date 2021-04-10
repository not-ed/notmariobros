#include "koopa.h"
#include <iostream>

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map) {
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	anim.SwitchTexture(textureRoaming[(angry)]);
	anim.SetAnimationSpeed(0.1f);

	injuryTimer.SetTime(INJURED_TIME, false);
}

CharacterKoopa::~CharacterKoopa() {

}

void CharacterKoopa::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);
	injuryTimer.Update(deltaTime);
	anim.Update(deltaTime);
	angry = pipeTravelFlag;

	if (angry) {
		m_movement_speed = KOOPA_ANGRY_SPEED;
	}
	else {
		m_movement_speed = KOOPA_SPEED;
	}

	if (!m_injured) {
		if (m_facing_direction == FACING_LEFT) {
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_left = false;
			m_moving_right = true;
		}
	}
	else {
		// Shouldn't be moving
		m_moving_left = false;
		m_moving_right = false;

		if (injuryTimer.IsExpired() && GetAlive()) { 
			FlipRightWayUp(); }
	}
}

void CharacterKoopa::Render() {
	//Draw sprite in the corresponding facing direction
	if (GetAlive())
	{
		if (m_injured) { 
			anim.SwitchTexture(textureStunned[(angry)]);
		}
		else {
			anim.SwitchTexture(textureRoaming[(angry)]);
		}
	}
	else {
		anim.SwitchTexture(textureDead[(angry)]);
	}
	

	if (m_facing_direction == FACING_RIGHT) { 
		anim.SetFlip(SDL_FLIP_NONE); 
	} else { 
		anim.SetFlip(SDL_FLIP_HORIZONTAL); 
	}

	anim.Render(m_position,0.0);

	Debug_RenderHitbox();
}

void CharacterKoopa::TakeDamage() {
	m_injured = true;
	Jump(INJURY_JUMP_FORCE);
	injuryTimer.Reset();
}

void CharacterKoopa::Jump(float force) {
	if (!m_jumping) {
		m_jump_force = force;
		m_jumping = true;
		m_can_jump = false;
	}
}

void CharacterKoopa::FlipRightWayUp() {
	FlipDirection();
	m_injured = false;
	anim.SwitchTexture(textureRoaming[(angry)]);
	Jump(INJURY_JUMP_FORCE);
}

void CharacterKoopa::FlipDirection() {
	if (m_facing_direction == FACING::FACING_LEFT) { 
		m_facing_direction = FACING::FACING_RIGHT; 
	}
	else { 
		m_facing_direction = FACING::FACING_LEFT;
	}
}

void CharacterKoopa::OnKill() {
	Character::OnKill();

	SoundManager::Instance()->PlaySound(SOUND::ID::ENEMY_DIE);
}