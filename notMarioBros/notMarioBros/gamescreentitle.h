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

//Forward declaration
class Texture2D;

class GameScreenTitle : GameScreen
{
public:
	GameScreenTitle(SDL_Renderer* renderer);
	~GameScreenTitle();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	bool SetUpLevel();
	HighScoreData scoreData;
	Timer scoreTableTimer;
	int displayedScores = 0;
	bool displayingScores = false;
	Animator logo = Animator(TEXTURE::ID::LOGO, 0.15f);
};

#endif