#include "koopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, FACING start_facing, float activation_time) : Character(renderer, start_position, map) {
	facingDirection = start_facing;
	position = start_position;
	injured = false;

	anim.SwitchTexture(textureRoaming[(angry)]);
	anim.SetAnimationSpeed(0.1f);

	injuryTimer.SetTime(INJURED_TIME, false);
	activationTimer.SetTime(activation_time, true);
}

void CharacterKoopa::Update(float delta_time, SDL_Event e) {
	if (activationTimer.IsExpired())
	{
		Character::Update(delta_time, e);
		injuryTimer.Update(delta_time);
		anim.Update(delta_time);

		// Become angry upon travelling through a level pipe.
		angry = pipeTravelFlag;

		if (angry) {
			movementSpeed = angryMovementSpeed;
		}
		else {
			movementSpeed = regularMovementSpeed;
		}

		if (!injured) {
			if (facingDirection == FACING_LEFT) {
				movingLeft = true;
				movingRight = false;
			}
			else if (facingDirection == FACING_RIGHT)
			{
				movingLeft = false;
				movingRight = true;
			}
		}
		else {
			// Shouldn't be moving if injured/stunned
			movingLeft = false;
			movingRight = false;

			// Flip right way up after being stunned for a fixed amount of time.
			if (injuryTimer.IsExpired() && IsAlive()) {
				FlipRightWayUp();
			}
		}
	}
	else activationTimer.Update(delta_time);
}

void CharacterKoopa::Render() {
	//Draw sprite in the corresponding facing direction
	if (IsAlive())
	{
		if (injured) { 
			anim.SwitchTexture(textureStunned[(angry)]);
		}
		else {
			anim.SwitchTexture(textureRoaming[(angry)]);
		}
	}
	else {
		anim.SwitchTexture(textureDead[(angry)]);
	}
	

	if (facingDirection == FACING_RIGHT) {
		anim.SetFlip(SDL_FLIP_NONE); 
	} else { 
		anim.SetFlip(SDL_FLIP_HORIZONTAL); 
	}

	anim.Render(position,0.0);
}

void CharacterKoopa::TakeDamage() {
	injured = true;
	Jump(INJURY_JUMP_FORCE);
	injuryTimer.Reset();
}

void CharacterKoopa::Jump(float force) {
	if (!jumping) {
		jumpForce = force;
		jumping = true;
		canJump = false;
	}
}

void CharacterKoopa::FlipRightWayUp() {
	// Change direction upon flipping right side up
	FlipDirection();

	injured = false;
	anim.SwitchTexture(textureRoaming[(angry)]);
	Jump(INJURY_JUMP_FORCE);
}

void CharacterKoopa::FlipDirection() {
	if (facingDirection == FACING::FACING_LEFT) {
		facingDirection = FACING::FACING_RIGHT;
	}
	else { 
		facingDirection = FACING::FACING_LEFT;
	}
}

void CharacterKoopa::OnKill() {
	Character::OnKill();
	SoundManager::Instance()->PlaySound(SOUND::ID::ENEMY_DIE);
}