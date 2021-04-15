#include "charactermario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map) : Character(renderer, start_position, map) {
	movementSpeed = MOVEMENTSPEED;

	anim.SwitchTexture(idleTexture);
	anim.SetAnimationSpeed(0.09f);

	spawnPoint = start_position;

	respawnTimer.SetTime(4.0f, false);
	invincibilityTimer.SetTime(3.5f, false);
}

void CharacterMario::Update(float delta_time, SDL_Event e) {
	respawnTimer.Update(delta_time);
	invincibilityTimer.Update(delta_time);

	if (IsAlive())
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == moveLeftKey) {
				movingLeft = true;
			}
			if (e.key.keysym.sym == moveRightKey) {
				movingRight = true;
			}
			if (e.key.keysym.sym == jumpKey) {
				if (canJump) { Jump(INITIAL_JUMP_FORCE); anim.SwitchTexture(jumpTexture); SoundManager::Instance()->PlaySound(SOUND::ID::PLAYER_JUMP);}
			}
			break;
		case SDL_KEYUP:
			if (e.key.keysym.sym == moveLeftKey) {
				movingLeft = false;
			}
			if (e.key.keysym.sym == moveRightKey) {
				movingRight = false;
			}
			break;
		default:
			break;
		}

		if (!canJump) {
			anim.SwitchTexture(jumpTexture);
		}
		else {
			if (movingLeft || movingRight) {
				anim.SwitchTexture(runTexture);
			}
			else {
				anim.SwitchTexture(idleTexture);
			}
		}
	}
	else {
		// Enough time has passed since dying.
		if (respawnTimer.IsExpired())
		{
			Respawn();
		}
	}
	
	Character::Update(delta_time, e);
	anim.Update(delta_time);

	//Update head hit box
	headHitBox = Rect2D{ position.x,position.y - 2,GetCollisionBox().width,4 };
}

void CharacterMario::Render() {

	if (movingLeft)
	{
		anim.SetFlip(SDL_FLIP_HORIZONTAL);
	}
	else if (movingRight) {
		anim.SetFlip(SDL_FLIP_NONE);
	}

	// Render the relevant texture and frame from the animator, if mario/luigi is currently invincible rendering will blink for the duration that this occurs.
	if (!Invincible() || (Invincible() && (int)(invincibilityTimer.RemainingTime() / .10) % 2 == 0)) {
		anim.Render(position, 0.0);
	}
}

void CharacterMario::OnKill() {
	Character::OnKill();

	remainingLives--;

	// Stay in place horionztally while dying.
	movingLeft = false;
	movingRight = false;

	anim.SwitchTexture(dieTexture);

	respawnTimer.Reset();

	SoundManager::Instance()->PlaySound(SOUND::ID::PLAYER_DIE);
}

void CharacterMario::Respawn() {
	// If the player still has at least 1 life left, then they can respawn.
	if (remainingLives != 0)
	{
		SetAlive(true);
		position = spawnPoint;
		invincibilityTimer.Reset();
	}
}

void CharacterMario::RenderGUI() {
	std::string hud_text = hudNamePrefix;
	hud_text.append(to_string(remainingLives));

	Text::Draw(hud_text, hudTextPosition, hudFont, hudFontAllignment);

	/*SDL_Rect boxt = SDL_Rect{ (int)position.x,(int)position.y - 2,(int)GetCollisionBox().width,4 };
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &boxt);
	SDL_SetRenderDrawColor(renderer,255,255,255,255);*/
}

void CharacterMario::ResetLives() {
	remainingLives = STARTING_LIFE_COUNT;
}