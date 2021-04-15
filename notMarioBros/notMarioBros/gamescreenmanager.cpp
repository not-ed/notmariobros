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
	if (currentScreen->IsRequestingScreenSwitch())
	{
		ChangeScreen(currentScreen->GetRequestedScreen());
	}

	if (e.type == SDL_KEYDOWN && currentScreenID == SCREENS::SCREEN_MENU)
	{
		if (e.key.keysym.sym == SDLK_1) { ChangeScreen(SCREEN_LEVEL1); }
		if (e.key.keysym.sym == SDLK_2) { ChangeScreen(SCREEN_LEVEL1_2P); }
	}
}

void GameScreenManager::ChangeScreen(SCREENS new_screen) {
	// Clear the old screen if it exists
	if (currentScreen != nullptr) {
		delete currentScreen;
	}

	// Keep track of the enum passed in.
	currentScreenID = new_screen;

	// Pointers cannot be set up inside a switch statement. So they need to be set up here first
	GameScreenTitle* tempScreen_title;
	GameScreenLevel1* tempScreen;

	switch (new_screen)
	{
	case SCREEN_MENU:
		tempScreen_title = new GameScreenTitle(renderer,&score);
		currentScreen = (GameScreen*)tempScreen_title;
		tempScreen_title = nullptr;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(renderer,&score, false);
		currentScreen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL1_2P:
		tempScreen = new GameScreenLevel1(renderer, &score, true);
		currentScreen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	default:
		break;
	}

}