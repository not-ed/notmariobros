#include "characterluigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map) : CharacterMario(renderer, start_position, map) {
	// Overide movement keys so they are not shared with CharacterMario
	moveLeftKey = SDLK_a;
	moveRightKey = SDLK_d;
	jumpKey = SDLK_w;

	// Override animation textures inherited from CharacterMario
	idleTexture = TEXTURE::ID::LUIGI_IDLE;
	runTexture = TEXTURE::ID::LUIGI_RUN;
	jumpTexture = TEXTURE::ID::LUIGI_JUMP;
	dieTexture = TEXTURE::ID::LUIGI_DIE;

	// Override hud rendering parameters
	hudFont = FONT::ID::LUIGI;
	hudFontAllignment = FONT::ALLIGNMENT::RIGHT;
	hudTextPosition = IntVector2D(SCREEN_WIDTH - 8, SCREEN_HEIGHT - 24);
	hudNamePrefix = "LUIGI: ";

	anim.SetFlip(SDL_FLIP_HORIZONTAL);
}