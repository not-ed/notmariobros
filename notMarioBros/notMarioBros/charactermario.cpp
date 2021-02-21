#include "charactermario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position) : Character(renderer, imagePath, start_position) {

}

void CharacterMario::Update(float deltaTime, SDL_Event e) {

	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_LEFT) {
			m_moving_left = true;
		}
		if (e.key.keysym.sym == SDLK_RIGHT) {
			m_moving_right = true;
		}
		if (e.key.keysym.sym == SDLK_UP) {
			m_jumping = true;
		}
		break;
	case SDL_KEYUP:
		if (e.key.keysym.sym == SDLK_LEFT) {
			m_moving_left = false;
		}
		if (e.key.keysym.sym == SDLK_RIGHT) {
			m_moving_right = false;
		}
		if (e.key.keysym.sym == SDLK_UP) {
			m_jumping = false;
		}
		break;
	default:
		break;
	}

	Character::Update(deltaTime, e);
}