#include "icicle.h"


CharacterIcicle::CharacterIcicle(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed) : CharacterKoopa(renderer, start_position, map, start_facing, movement_speed)
{
	// Only the standard roaming texture needs to be set for an Icicle, as they will die and be removed immediately upon being stunned/injured.
	textureRoaming[0] = TEXTURE::ID::ICICLE;

	regularMovementSpeed = ICICLE_SPEED;
	angryMovementSpeed = 0;
	std::cout << "ICICLE" << std::endl;

	type = ENEMY_TYPE::ICICLE;
}

void CharacterIcicle::Update(float delta_time, SDL_Event e) {
	//std::cout << GetEnemyType() << std::endl;
	CharacterKoopa::Update(delta_time,e);
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
	//TODO: Spill out coins
	std::cout << "Killed Type:" << GetEnemyType() << std::endl;
	// Immediately move off screen, unlike other enemies which will jump
	position.y = SCREEN_HEIGHT+100;
}