#include "characterluigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map) : Character(renderer, start_position, map) {
	movementSpeed = MOVEMENTSPEED;
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e) {

	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_a) {
			movingLeft = true;
		}
		if (e.key.keysym.sym == SDLK_d) {
			movingRight = true;
		}
		if (e.key.keysym.sym == SDLK_w) {
			if (canJump) { Jump(INITIAL_JUMP_FORCE); }
		}
		break;
	case SDL_KEYUP:
		if (e.key.keysym.sym == SDLK_a) {
			movingLeft = false;
		}
		if (e.key.keysym.sym == SDLK_d) {
			movingRight = false;
		}
		break;
	default:
		break;
	}

	Character::Update(deltaTime, e);
}