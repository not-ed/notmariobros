#pragma once
#ifndef POWBLOCK_H
#define POWBLOCK_H

#include <SDL.h>
#include "commons.h"
#include "levelmap.h"
#include "texture2d.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* level);
	~PowBlock();

	void Render();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_single_sprite_w, m_single_sprite_h); }
	void TakeHit();
	bool IsAvailable() { return m_num_hits_left > 0; }

private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;

};


#endif