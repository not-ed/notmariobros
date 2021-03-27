#include "charactermario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map) {
	m_movement_speed = MOVEMENTSPEED;
	anim.SwitchTexture(TEXTURE::ID::MARIO_IDLE);
	anim.SetAnimationSpeed(0.14f);
}

void CharacterMario::Update(float deltaTime, SDL_Event e) {
	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_LEFT) {
			m_moving_left = true;
			anim.SetFlip(SDL_FLIP_HORIZONTAL);
		}
		if (e.key.keysym.sym == SDLK_RIGHT) {
			m_moving_right = true;
			anim.SetFlip(SDL_FLIP_NONE);
		}
		if (e.key.keysym.sym == SDLK_UP) {
			if (m_can_jump) { Jump(INITIAL_JUMP_FORCE); anim.SwitchTexture(TEXTURE::ID::MARIO_JUMP); }
		}
		break;
	case SDL_KEYUP:
		if (e.key.keysym.sym == SDLK_LEFT) {
			m_moving_left = false;
		}
		if (e.key.keysym.sym == SDLK_RIGHT) {
			m_moving_right = false;
		}
		break;
	default:
		break;
	}

	if (!m_can_jump) {
		anim.SwitchTexture(TEXTURE::ID::MARIO_JUMP);
	}
	else {
		if (m_moving_left || m_moving_right) {
			anim.SwitchTexture(TEXTURE::ID::MARIO_RUN);
		}
		else {
			anim.SwitchTexture(TEXTURE::ID::MARIO_IDLE);
		}
	}

	Character::Update(deltaTime, e);
	anim.Update(deltaTime);
}

void CharacterMario::Render() {
	anim.Render(m_position,0.0);
}