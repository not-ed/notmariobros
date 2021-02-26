#include "gamescreenlevel1.h"
#include <iostream>
#include "texture2d.h"
#include "collisions.h"
// The required parameters also need to be passed through the GameScreens constructor.
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	m_level_map = nullptr;

	SetUpLevel();
}


GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;

	delete mario_character;
	mario_character = nullptr;

	delete luigi_character;
	luigi_character = nullptr;
}

void GameScreenLevel1::Render() {
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//Render characters
	mario_character->Render();
	luigi_character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	//Update character
	mario_character->Update(deltaTime, e);
	luigi_character->Update(deltaTime, e);

	// Temporary Collision Tests
	if (Collisions::Instance()->Circle(mario_character,luigi_character)) {
		cout << "Circle collision made!" << endl;
	}
	if (Collisions::Instance()->Box(mario_character->GetCollisionBox(),luigi_character->GetCollisionBox())) {
		cout << "Box collision made!" << endl;
	}
}

bool GameScreenLevel1::SetUpLevel() {
	// Load background texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/lvl1background.png"))
	{
		std::cerr << "[!] Failed to load background texture." << std::endl;
		return false;
	}

	SetLevelMap();

	// Setting up player character
	mario_character = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330),m_level_map);
	luigi_character = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(432, 330),m_level_map);

	//TODO: Temporary POW-block removal test, take this out later.
	//m_level_map->ChangeTileAt(8, 7, 0);
	//m_level_map->ChangeTileAt(8, 8, 0);

	return true;
}

void GameScreenLevel1::SetLevelMap() {
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	//Clear any old maps
	if (m_level_map != nullptr) {
		delete m_level_map;
	}

	//Set new map
	m_level_map = new LevelMap(map);
}