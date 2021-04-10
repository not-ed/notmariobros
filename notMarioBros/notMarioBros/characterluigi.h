#pragma once
#ifndef CHARACTERLUIGI_H
#define CHARACTERLUIGI_H

#include "character.h"

//TODO: Nothing needs to be done to character luigi so far, Luigi only differs from mario in appearance so this can inherit from CharacterMario later.

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, Vector2D start_position, LevelMap* map);
	//~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e);
private:

};

#endif