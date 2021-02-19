#pragma once
#pragma once
#ifndef GAMESCREENTITLE_H
#define GAMESCREENTITLE_H

#include "gamescreen.h"
#include "commons.h"

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
	Texture2D* m_background_texture;

	bool SetUpLevel();
};

#endif