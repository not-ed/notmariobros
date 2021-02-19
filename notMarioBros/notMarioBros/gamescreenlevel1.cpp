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

	delete my_character;
	my_character = nullptr;
}

void GameScreenLevel1::Render() {
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//Render character
	my_character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	//Update character
	my_character->Update(deltaTime, e);
}

bool GameScreenLevel1::SetUpLevel() {
	// Load background texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cerr << "[!] Failed to load background texture." << std::endl;
		return false;
	}

	// Setting up player character
	my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 330));

	return true;
}