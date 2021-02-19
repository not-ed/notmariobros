#pragma once
#ifndef GAMESCREENMANAGER_H
#define GAMESCREENMANAGER_H

#include <SDL.h>
#include "commons.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS new_screen);

private:
	SDL_Renderer* m_renderer;
	GameScreen* m_current_screen;
};

#endif