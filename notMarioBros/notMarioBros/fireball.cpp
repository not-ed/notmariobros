#include "fireball.h"

FireBall::FireBall(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, FACING start_facing, TEXTURE::ID texture) : Character(renderer, start_position, map)
{
	anim.SwitchTexture(texture);
	anim.SetAnimationSpeed(0.05f);

	facingDirection = start_facing;

	movementSpeed = 32.0f;

	Jump(160.0f);
}

void FireBall::Update(float delta_time, SDL_Event e) {
	anim.Update(delta_time);

	// Fireballs need to ignore collision, so AddGravity will not be called despite the option being there.
	position.y += -jumpForce * delta_time;
	jumpForce -= JUMP_FORCE_DECREMENT * delta_time;

	if (facingDirection == FACING_LEFT) { MoveLeft(delta_time); }
	if (facingDirection == FACING_RIGHT) { MoveRight(delta_time); }
}

void FireBall::Render() {
	anim.Render(position, 0.0);
}