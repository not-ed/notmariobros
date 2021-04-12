#include "crab.h"

CharacterCrab::CharacterCrab(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, FACING start_facing) : CharacterKoopa(renderer, start_position, map, start_facing)
{
	// Override texture IDs inherited from Koopa class
	textureRoaming[0] = TEXTURE::ID::CRAB;
	textureRoaming[1] = TEXTURE::ID::CRAB_ANGRY;
	textureStunned[0] = TEXTURE::ID::CRAB_STUN;
	textureStunned[1] = TEXTURE::ID::CRAB_ANGRY_STUN;
	textureDead[0] = TEXTURE::ID::CRAB_DIE;
	textureDead[1] = TEXTURE::ID::CRAB_ANGRY_DIE;

	regularMovementSpeed = CRAB_SPEED;
	angryMovementSpeed = CRAB_ANGRY_SPEED;

	fireballSpawnTimer.SetTime(fireballSpawnFrequency, true);

	type = ENEMY_TYPE::CRAB;
}

CharacterCrab::~CharacterCrab()
{
	// Destroy any held fireballs if they haven't been handed off to something else already
	for (int i = 0; i < heldFireballs.size(); i++)
	{
		delete heldFireballs[i];
	}
}

void CharacterCrab::Update(float delta_time, SDL_Event e) {
	CharacterKoopa::Update(delta_time, e);
	fireballSpawnTimer.Update(delta_time);

	if (fireballSpawnTimer.IsExpired() && IsAlive() && !GetInjured())
	{
		CreateFireballs();
		fireballSpawnTimer.Reset();
	}

	// Increase fireball frequency if angry
	if (angry)
	{
		fireballSpawnTimer.SetTime(fireballSpawnFrequencyAngry, false);
	}
}

FireBall* CharacterCrab::FetchFireball() {
	// Are there any fireballs to fetch?
	if (heldFireballs.size() > 0)
	{
		FireBall* fetched_fireball = heldFireballs[0];
		// Pointer no longer needs to be held in the vector as it is going to be passed on
		heldFireballs.erase(heldFireballs.begin());

		return fetched_fireball;
	}
	return nullptr;
}

void CharacterCrab::CreateFireballs() {
	heldFireballs.push_back(new FireBall(renderer,Vector2D(position.x + (anim.GetFrameWidth()/2), position.y),currentLevelMap,FACING::FACING_LEFT,fireballTexture[angry]));
	heldFireballs.push_back(new FireBall(renderer, Vector2D(position.x + (anim.GetFrameWidth() / 2), position.y), currentLevelMap, FACING::FACING_RIGHT, fireballTexture[angry]));
}