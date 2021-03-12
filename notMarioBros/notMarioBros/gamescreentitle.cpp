#include "gamescreentitle.h"
#include <iostream>
#include "texture2d.h"
#include "soundmanager.h"

// The required parameters also need to be passed through the GameScreens constructor.
GameScreenTitle::GameScreenTitle(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
}


GameScreenTitle::~GameScreenTitle()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

void GameScreenTitle::Render() {
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenTitle::Update(float deltaTime, SDL_Event e) {

}

bool GameScreenTitle::SetUpLevel() {
	SoundManager::Instance()->StopMusic();

	// Load background texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/titletest.bmp"))
	{
		std::cerr << "[!] Failed to load background texture." << std::endl;
		return false;
	}

	SoundManager::Instance()->PlayMusic(MUSIC::ID::UNDERWORLD);

	return true;
}