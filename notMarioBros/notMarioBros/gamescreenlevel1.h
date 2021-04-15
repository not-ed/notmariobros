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
	GameScreenLevel1(SDL_Renderer* game_renderer, ScoreCounter* score_counter, bool include_luigi);
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
	// An array that indexes the mario and luigi pointers for the sake of preventing duplication in some areas.
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
	void CreateKoopa(Vector2D position, FACING direction, float activation_time);
	void CreateCrab(Vector2D position, FACING direction, float activation_time);
	void CreateIcicle(Vector2D position, FACING direction, float activation_time);
	// Any enemies that exist in the scene so far.
	vector<CharacterKoopa*> enemies;
	
	// Any coins that exist in the level, which update and behave independently from enemies.
	void UpdateCoins(float delta_time, SDL_Event e);
	vector<Coin*> coins;

	// Any fireballs that exist in the level, which update and behave independently from enemies.
	void UpdateFireBalls(float delta_time, SDL_Event e);
	vector<FireBall*> fireballs;

	// Query if an injured/killed enemy is an Icicle enemy, in order to determine whether to spawn coins on enemy death.
	void QueryIcicleInjury(CharacterKoopa* enemy);

	// How frequently each type of enemy will spawn.
	Timer koopaSpawnTimer;
	Timer crabSpawnTimer;
	Timer icicleSpawnTimer;

	// A window that can be displayed at the end of a game for the player to submit their name to the high score table.
	ScoreNameEntryWindow scoreNameWindow;

	// How long the game over sequence is displayed at the end of a game.
	Timer gameOverTimer;

	// Is the game being played 2 player?
	bool isTwoPlayer = false;
};

#endif