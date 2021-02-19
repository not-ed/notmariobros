#include "gamescreenmanager.h"
#include "gamescreen.h"
#include "gamescreenlevel1.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {
	m_renderer = renderer;
	m_current_screen = nullptr;

	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager() {
	// This only needs to be set to null as it would have been holding the renderer PASSED IN when it was constructed.
	m_renderer = nullptr;

	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render() {
	m_current_screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e) {
	m_current_screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen) {
	// Clear the old screen if it exists
	if (m_current_screen != nullptr) {
		delete m_current_screen;
	}

	// Pointers cannot be set up inside a switch statement.
	GameScreenLevel1* tempScreen;

	switch (new_screen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempScreen;
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