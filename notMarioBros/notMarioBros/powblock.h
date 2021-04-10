#pragma once
#ifndef POWBLOCK_H
#define POWBLOCK_H

#include <SDL.h>
#include "commons.h"
#include "levelmap.h"
#include "texture2d.h"
#include "soundmanager.h"
#include "animator.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* level);
	~PowBlock();

	void Render();
	
	Rect2D GetCollisionBox() { return Rect2D(position.x, position.y, anim.GetFrameWidth(), anim.GetFrameHeight()); }

	void TakeHit();

	// Are any hits left in the POW block?
	bool IsAvailable() { return hitsLeft > 0; }

private:
	SDL_Renderer* renderer;

	Vector2D position;

	LevelMap* levelMap;

	int hitsLeft;
	
	Animator anim = Animator(TEXTURE::ID::POW_BLOCK, 0.0f);
};

#endif