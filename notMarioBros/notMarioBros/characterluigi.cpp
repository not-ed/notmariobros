#include "characterluigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map) {
	
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e) {

	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_a) {
			m_moving_left = true;
		}
		if (e.key.keysym.sym == SDLK_d) {
			m_moving_right = true;
		}
		if (e.key.keysym.sym == SDLK_w) {
			if (m_can_jump) { Jump(); }
		}
		break;
	case SDL_KEYUP:
		if (e.key.keysym.sym == SDLK_a) {
			m_moving_left = false;
		}
		if (e.key.keysym.sym == SDLK_d) {
			m_moving_right = false;
		}
		break;
	default:
		break;
	}

	Character::Update(deltaTime, e);
}