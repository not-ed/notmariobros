#pragma once
#ifndef GAMESCREENLEVEL1_H
#define GAMESCREENLEVEL1_H

#include <iostream>
#include <vector>
#include "gamescreen.h"
#include "soundmanager.h"
#include "texturemanager.h"
#include "timer.h"
#include "levelmap.h"
#include "collisions.h"
#include "commons.h"
#include "powblock.h"
#include "coin.h"
#include "character.h"
#include "charactermario.h"
#include "characterluigi.h"
#include "koopa.h"
#include "icicle.h"
#include "crab.h"

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* game_renderer, ScoreCounter* score_counter);
	~GameScreenLevel1();

	void Render() override;
	void Update(float delta_time, SDL_Event e) override;

	// Update the level's POW block if used by mario/luigi
	void UpdatePOWBlock();

	// Query if a character is going off screen horizontally, and 
	void QueryLevelBounds(Character* chara);

private:
	Texture2D* backgroundTexture;

	// Set up relevant level components (backgrounds, objects, enemies, players, etc)
	bool SetUpLevel();

	// Data on tiles that make up a levels composition.
	LevelMap* levelMap;
	void SetLevelMap();

	CharacterMario* mario = nullptr;
	CharacterLuigi* luigi = nullptr;
	CharacterMario* players[2];

	PowBlock* powBlock;

	// Screen Shake
	Timer screenShakeTimer;
	// How much the screen is shaking
	float accumulatedWobble; 
	// The y-position of the level background with screen-shake factored in.
	float backgroundYPos;
	void DoScreenShake();
	
	// Enemies
	void UpdateEnemies(float delta_time, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction);
	void CreateCrab(Vector2D position, FACING direction);
	void CreateIcicle(Vector2D position, FACING direction);
	// Any enemies that exist in the scene so far.
	vector<CharacterKoopa*> enemies;
	
	void UpdateCoins(float delta_time, SDL_Event e);
	// Any coins that exist in the level, which update and behave independently from enemies.
	vector<Coin*> coins;

	void UpdateFireBalls(float delta_time, SDL_Event e);
	// Any fireballs that exist in the level, which update and behave independently from enemies.
	vector<FireBall*> fireballs;

	// Query if an injured/killed enemy is an Icicle enemy, in order to determine whether to spawn coins on enemy death.
	void QueryIcicleInjury(CharacterKoopa* enemy);

	// TODO: this should be removed as levels move towards using a manifest of enemies and not spawning them endlessly.
	float koopa_spawn_frequency = 9.0f;
	float last_koopa_spawn;
	FACING koopa_starting_direction;

	// A window that can be displayed at the end of a game for the player to submit their name to the high score table.
	ScoreNameEntryWindow scoreNameWindow;

	// How long the game over sequence is displayed at the end of a game.
	Timer gameOverTimer;
};

#endif