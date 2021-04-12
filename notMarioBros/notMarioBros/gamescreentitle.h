#pragma once
#pragma once
#ifndef GAMESCREENTITLE_H
#define GAMESCREENTITLE_H

#include "gamescreen.h"
#include "commons.h"
#include "textrenderer.h"
#include "texturemanager.h"
#include "score.h"
#include "timer.h"
#include "animator.h"

class Texture2D;

class GameScreenTitle : GameScreen
{
public:
	GameScreenTitle(SDL_Renderer* game_renderer, ScoreCounter* score_counter);

	void Render() override;
	void Update(float delta_time, SDL_Event e) override;

private:
	bool SetUpLevel();

	// Packet of data holding the top 10 high scores read from file
	HighScoreData scoreData;

	// Timer for displaying high score table entries and cycling between the table and Game Start prompts.
	Timer scoreTableTimer;
	// How many entries have been displayed so far when displaying the high score table
	int displayedScores = 0;
	// Is the menu currently displaying the Game Start prompts, or the high score table?
	bool displayingScores = false;

	// Game logo
	Animator logo = Animator(TEXTURE::ID::LOGO, 0.15f);
};

#endif