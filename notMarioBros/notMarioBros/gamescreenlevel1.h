#pragma once
#ifndef GAMESCREENLEVEL1_H
#define GAMESCREENLEVEL1_H

#include "gamescreen.h"
#include "commons.h"
#include "character.h"
#include "charactermario.h"
#include "characterluigi.h"
#include "levelmap.h"

//Forward declarations
class Texture2D;
class Character;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	Texture2D* m_background_texture;

	bool SetUpLevel();

	LevelMap* m_level_map;
	void SetLevelMap();

	CharacterMario* mario_character;
	CharacterLuigi* luigi_character;
};

#endif