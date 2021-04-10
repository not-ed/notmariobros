#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include <iostream>
#include "commons.h"
#include "constants.h"
#include "texture2d.h"
#include "levelmap.h"
#include "animator.h"
#include "soundmanager.h"

using namespace std;

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
	float GetCollisionRadius();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, anim.GetFrameWidth(), anim.GetFrameHeight()); }

	bool IsJumping() { return m_jumping; }
	void CancelJump();

	void SetAlive(bool isAlive);
	bool GetAlive() { return m_alive; }

	void Debug_RenderHitbox();

	bool InLevelBounds();

	void TriggerPipeFlag() { pipeTravelFlag = true; }
private:
	bool m_alive;
	LevelMap* m_current_level_map;
protected:
	// The character has flipped across the level through the pipe at least once.
	bool pipeTravelFlag = false;

	FACING m_facing_direction;

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

	float m_collision_radius;

	bool m_moving_left;
	bool m_moving_right;

	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;

	float m_movement_speed;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	virtual void Jump(float force);
	virtual void OnKill();
	

	Animator anim = Animator(TEXTURE::ID::NONE,0.0f);

};

#endif