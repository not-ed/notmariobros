#include "coin.h"

Coin::Coin(SDL_Renderer* game_renderer, Vector2D start_position, LevelMap* map) : Character(game_renderer,start_position,map)
{
	anim.SwitchTexture(TEXTURE::ID::COIN);
	anim.SetAnimationSpeed(0.064f);
	// Set the current animator to a random frame just so a pair of coins don't all look exactly the same.
	anim.SetFrame(rand() % TextureManager::Instance()->GetFrameCount(TEXTURE::ID::COIN));

	lifetimeTimer.SetTime(8.5f,true);

	movementSpeed = 1.0f * (rand() % 48);
	movingLeft = (bool)(rand()%2);
	movingRight = !movingLeft;

	Jump(COIN_INITIAL_JUMP_FORCE);
}

Coin::~Coin()
{

}

void Coin::Update(float delta_time, SDL_Event e) {
	Character::Update(delta_time,e);
	anim.Update(delta_time);
	lifetimeTimer.Update(delta_time);
	if (!jumping && canJump)
	{
		Jump(COIN_BOUNCE_FORCE);
	}
}

void Coin::Render() {
	// Render normally, or start blinking if the coin is going to vanish in under 3 seconds
	if (lifetimeTimer.RemainingTime() > 3.0f || ((int)(lifetimeTimer.RemainingTime() / .10) % 2 == 0))
	{
		anim.Render(position, 0.0);
	}
}