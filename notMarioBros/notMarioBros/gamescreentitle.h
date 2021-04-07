#pragma once
#pragma once
#ifndef GAMESCREENTITLE_H
#define GAMESCREENTITLE_H

#include "gamescreen.h"
#include "commons.h"
#include "textrenderer.h"
#include "texturemanager.h"
#include "score.h"

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
};

#endif