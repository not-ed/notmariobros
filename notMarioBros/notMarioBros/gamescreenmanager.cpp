#include "gamescreenmanager.h"
#include "gamescreen.h"
#include "gamescreenlevel1.h"
#include "gamescreentitle.h"

#include <iostream>

GameScreenManager::GameScreenManager(SDL_Renderer* game_renderer, SCREENS starting_screen) {
	renderer = game_renderer;

	currentScreen = nullptr;

	ChangeScreen(starting_screen);
}

GameScreenManager::~GameScreenManager() {
	// This only needs to be set to null as it would have been holding the renderer PASSED IN when it was constructed.
	renderer = nullptr;

	delete currentScreen;
	currentScreen = nullptr;
}

void GameScreenManager::Render() {
	currentScreen->Render();
}

void GameScreenManager::Update(float delta_time, SDL_Event e) {
	currentScreen->Update(delta_time, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen) {
	// Clear the old screen if it exists
	if (currentScreen != nullptr) {
		delete currentScreen;
	}

	// Pointers cannot be set up inside a switch statement.
	GameScreenTitle* tempScreen_title;
	GameScreenLevel1* tempScreen;
	

	switch (new_screen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		tempScreen_title = new GameScreenTitle(renderer);
		currentScreen = (GameScreen*)tempScreen_title;
		tempScreen_title = nullptr;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(renderer);
		currentScreen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL2:
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}

}