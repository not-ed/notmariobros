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
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	//~CharacterMario();

	void Update(float deltaTime, SDL_Event e);
	void Render();
	bool Invincible() { return !invincibilityTimer.IsExpired(); }
	void RenderGUI();
	Rect2D GetHeadHitBox() { return headHitBox; }
protected:
	void OnKill();
	void Respawn();
	Timer respawnTimer;
	Timer invincibilityTimer;
	Vector2D spawnPoint;
	int remainingLives = 3;
	Rect2D headHitBox = Rect2D{ 0,0,0,0 };
};

#endif