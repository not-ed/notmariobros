#pragma once
#ifndef FIREBALL_H
#define FIREBALL_H

#include "character.h"

class FireBall : public Character
{
public:
	FireBall(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map, FACING start_facing, TEXTURE::ID texture);

	void Update(float delta_time, SDL_Event e);
	void Render();

private:

};


#endif