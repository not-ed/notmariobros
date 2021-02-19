#include "gamescreenlevel1.h"
#include <iostream>
#include "texture2d.h"

// The required parameters also need to be passed through the GameScreens constructor.
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
}


GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

void GameScreenLevel1::Render() {
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {

}

bool GameScreenLevel1::SetUpLevel() {
	// Load background texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cerr << "[!] Failed to load background texture." << std::endl;
		return false;
	}
	return true;
}