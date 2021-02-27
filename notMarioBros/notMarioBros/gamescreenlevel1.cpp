#include "gamescreenlevel1.h"
#include <iostream>
#include "texture2d.h"
#include "collisions.h"
#include "powblock.h"

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

	delete m_pow_block;
	m_pow_block = nullptr;
}

void GameScreenLevel1::Render() {
	m_background_texture->Render(Vector2D(0,m_background_yPos), SDL_FLIP_NONE);

	//Render characters
	mario_character->Render();
	luigi_character->Render();

	m_pow_block->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	// Screen shake (if applicable)
	if (m_screenshake) {
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 8.0;

		// End screen shake.
		if (m_shake_time <= 0.0f) {
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

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

	UpdatePOWBlock();
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

	// Setting up POW block
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;

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

void GameScreenLevel1::UpdatePOWBlock() {
	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(),mario_character->GetCollisionBox()) && m_pow_block->IsAvailable())
	{
		if (mario_character->IsJumping()) {
			DoScreenShake();
			m_pow_block->TakeHit();
			mario_character->CancelJump();
		}
	}
}

void GameScreenLevel1::DoScreenShake() {
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}