#pragma once
#ifndef CHARACTERLUIGI_H
#define CHARACTERLUIGI_H

#include "charactermario.h"

class CharacterLuigi : public CharacterMario
{
public:
	CharacterLuigi(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map);
};

#endif