#pragma once
#ifndef CHARACTERMARIO_H
#define CHARACTERMARIO_H

#include "character.h"
#include "textrenderer.h"
#include "timer.h"
#include <string>

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map);

	void Update(float delta_time, SDL_Event e);
	void Render();

	// Has mario/luigi just respawned and on cooldown?
	bool Invincible() { return !invincibilityTimer.IsExpired(); }

	// Rendering which is called last by the game screen - intended for GUI purposes to guarantee whatever is drawn is shown at the front.
	void RenderGUI();

	// Get the hit box from mario/luigi's head - used for damaging enemies without the use of a POW block.
	Rect2D GetHeadHitBox() { return headHitBox; }

	// Reset Live count to the starting amount of 3
	void ResetLives();

	// Has the player completely run out of lives?
	bool OutOfGame() { return (remainingLives == 0 && respawnTimer.IsExpired()); }
protected:
	void OnKill();

	// Return to spawnPoint after being killed.
	void Respawn();
	// How long to wait until trying to respawn after being killed.
	Timer respawnTimer;
	// How long until mario/luigi can be killed again after respawning.
	Timer invincibilityTimer;

	// Initial starting position, and where to return to upon respawning.
	Vector2D spawnPoint;

	static int remainingLives;
	
	// Used in collision detection for damaging enemies without the use of a POW block.
	Rect2D headHitBox = Rect2D{ 0,0,0,0 };

	// Relevant texture IDs for actions such as running, jumping, dying etc
	TEXTURE::ID idleTexture = TEXTURE::ID::MARIO_IDLE;
	TEXTURE::ID runTexture = TEXTURE::ID::MARIO_RUN;
	TEXTURE::ID jumpTexture = TEXTURE::ID::MARIO_JUMP;
	TEXTURE::ID dieTexture = TEXTURE::ID::MARIO_DIE;

	// Font, allignment, and position to use for drawing remaining lives as text in RenderGUI.
	FONT::ID hudFont = FONT::ID::MARIO;
	FONT::ALLIGNMENT hudFontAllignment = FONT::ALLIGNMENT::LEFT;
	IntVector2D hudTextPosition = IntVector2D(8, SCREEN_HEIGHT - 24);
	// Text/name to display before the remaining life count on the HUD.
	std::string hudNamePrefix = "MARIO: ";
};

#endif