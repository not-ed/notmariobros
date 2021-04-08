#pragma once
#ifndef GAMESCREENLEVEL1_H
#define GAMESCREENLEVEL1_H

#include "gamescreen.h"
#include "commons.h"
#include "character.h"
#include "charactermario.h"
#include "characterluigi.h"
#include "koopa.h"
#include "levelmap.h"
#include <vector>
#include "texturemanager.h"

//Forward declarations
class Texture2D;
class Character;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePOWBlock();

private:
	Texture2D* m_background_texture;

	bool SetUpLevel();

	LevelMap* m_level_map;
	void SetLevelMap();

	CharacterMario* mario_character;
	CharacterLuigi* luigi_character;

	PowBlock* m_pow_block;


	// Screen Shake
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	void DoScreenShake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	vector<CharacterKoopa*> m_enemies;

	float koopa_spawn_frequency = 9.0f;
	float last_koopa_spawn;
	FACING koopa_starting_direction;
};

#endif