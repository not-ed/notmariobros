#include "icicle.h"


CharacterIcicle::CharacterIcicle(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, FACING start_facing) : CharacterKoopa(renderer, start_position, map, start_facing)
{
	// Only the standard roaming texture needs to be set for an Icicle, as they will die and be removed immediately upon being stunned/injured.
	textureRoaming[0] = TEXTURE::ID::ICICLE;

	regularMovementSpeed = ICICLE_SPEED;
	angryMovementSpeed = 0;

	type = ENEMY_TYPE::ICICLE;
}

void CharacterIcicle::Update(float delta_time, SDL_Event e) {
	CharacterKoopa::Update(delta_time,e);
	// Die immediately upon exiting through a pipe and getting angry.
	if (angry || GetInjured())
	{
		SetAlive(false);
	}
}

Coin* CharacterIcicle::DropCoin() {
	Coin* coin = new Coin(renderer, Vector2D(position.x + (anim.GetFrameWidth() / 2), position.y), currentLevelMap);
	return coin;
}

void CharacterIcicle::OnKill() {
	// Immediately move off screen, hiding the jump effect from the player that normally plays.
	position.y = SCREEN_HEIGHT+100;
}