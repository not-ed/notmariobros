#pragma once
#ifndef CHARACTERLUIGI_H
#define CHARACTERLUIGI_H

#include "character.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	//~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e);
private:

};

#endif