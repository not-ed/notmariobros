#include "koopa.h"
#include <iostream>

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map) {
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}

CharacterKoopa::~CharacterKoopa() {

}

void CharacterKoopa::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);

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

		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0 && GetAlive()) { 
			FlipRightWayUp(); }
	}
}

void CharacterKoopa::Render() {
	// The leftmost position of the sprite we want to draw
	float left = 0.0f;

	// If injured, then use the second frame on the koopa sprite sheet (injured)
	if (m_injured) { left = m_single_sprite_w; }

	// Establish portion of koopa sprite sheet to be drawn
	SDL_Rect portion_of_sprite = {left,0,m_single_sprite_w,m_single_sprite_h};

	// Establish where to draw current sprite
	SDL_Rect destRect = { (int)(m_position.x),(int)(m_position.y),m_single_sprite_w,m_single_sprite_h };

	//Draw sprite in the corresponding facing direction
	if (m_facing_direction == FACING_RIGHT) { m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE); }
	else { m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL); }
}

void CharacterKoopa::TakeDamage() {
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump(INJURY_JUMP_FORCE);
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