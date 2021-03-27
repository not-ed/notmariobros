#pragma once
#ifndef CHARACTERMARIO_H
#define CHARACTERMARIO_H

#include "character.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	//~CharacterMario();

	void Update(float deltaTime, SDL_Event e);
	void Render();
private:

};

#endif