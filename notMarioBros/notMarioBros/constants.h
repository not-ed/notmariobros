#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

// Game Window / Screen dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

// Mario/luigi movement speed
#define MOVEMENTSPEED 128.0f

// How many lives mario/luigi start a game with.
#define STARTING_LIFE_COUNT 3

#define GRAVITY 160.0f

#define INITIAL_JUMP_FORCE 500.00f
#define JUMP_FORCE_DECREMENT 400.0f

// How many tiles wide/tall any given map is
#define MAP_WIDTH 16
#define MAP_HEIGHT 13

// The size of a map tile in pixels
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

// How long a screen shake effect should be applied when using a POW block
#define SHAKE_DURATION .25f

// How long an enemy stays still when being stunned or injured
#define INJURED_TIME 2.5f
// How high a enemy jumps into the air when stunned
#define INJURY_JUMP_FORCE 300.0f
// How high a enemy jumps into the air when killed
#define KILL_JUMP_FORCE 400.0f

// Coin Jump/bounce forces
#define COIN_INITIAL_JUMP_FORCE 275.0f
#define COIN_BOUNCE_FORCE 250.0f

// Koopa movement speeds
#define KOOPA_SPEED 64.0f
#define KOOPA_ANGRY_SPEED 128.0f

// Crab movement speeds
#define CRAB_SPEED 48.0f
#define CRAB_ANGRY_SPEED 72.0f

// Icicle movement speeds
#define ICICLE_SPEED 150.0f

// Scoring values
#define SCORE_COIN_COLLECTED 1500
#define SCORE_POW_BLOCK_STUN 100
#define SCORE_ENEMY_STUNNED 25
#define SCORE_KOOPA_KILLED 150
#define SCORE_CRAB_KILLED 230
#define SCORE_LEVEL_COMPLETED 500

// How long to display the game over screen for
#define GAME_OVER_TIME 3.0f

// Maximum possible Enemy spawn times
#define KOOPA_SPAWN_TIME_MAX 15.0f
#define CRAB_SPAWN_TIME_MAX 30.0f
#define ICICLE_SPAWN_TIME_MAX 40.0f

#endif