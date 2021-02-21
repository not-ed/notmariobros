#include "characterluigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position) : Character(renderer, imagePath, start_position) {
	
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
			m_jumping = true;
		}
		break;
	case SDL_KEYUP:
		if (e.key.keysym.sym == SDLK_a) {
			m_moving_left = false;
		}
		if (e.key.keysym.sym == SDLK_d) {
			m_moving_right = false;
		}
		if (e.key.keysym.sym == SDLK_w) {
			m_jumping = false;
		}
		break;
	default:
		break;
	}

	Character::Update(deltaTime, e);
}