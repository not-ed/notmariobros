#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <SDL.h>
#include "commons.h"
#include "constants.h"
#include "levelmap.h"
#include "animator.h"
#include "soundmanager.h"

using namespace std;

class Character
{
public:
	Character(SDL_Renderer* game_renderer, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Update(float delta_time, SDL_Event e);
	virtual void Render() {};

	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	// Collision detection
	float GetCollisionRadius();
	Rect2D GetCollisionBox() { return Rect2D(position.x, position.y, anim.GetFrameWidth(), anim.GetFrameHeight()); }

	bool IsJumping() { return jumping; }
	void CancelJump();

	void SetAlive(bool is_alive);
	bool IsAlive() { return alive; }

	//TODO: this should be remove later
	void Debug_RenderHitbox();

	// Is the character COMPLETELY inside the level bounds?
	bool InLevelBounds();

	// Trigger a special flag upon looping around a level axis via a pipe
	void TriggerPipeFlag() { pipeTravelFlag = true; }
private:
	bool alive;
protected:
	// The character has been through a pipe at least once.
	bool pipeTravelFlag = false;

	FACING facingDirection;

	SDL_Renderer* renderer;
	Vector2D position;

	float collisionRadius;

	bool movingLeft;
	bool movingRight;
	float movementSpeed;
	virtual void MoveLeft(float delta_time);
	virtual void MoveRight(float delta_time);

	bool jumping;
	bool canJump;
	float jumpForce;
	virtual void Jump(float force);
	virtual void AddGravity(float delta_time);

	// Triggered when the character is "killed" by setting alive to false
	virtual void OnKill();

	// The center of the character on the x axis
	int centralXPosition = 0;
	// The position of the character's "foot"
	int footPosition = 0;

	Animator anim = Animator(TEXTURE::ID::NONE,0.0f);

	LevelMap* currentLevelMap;
};

#endif