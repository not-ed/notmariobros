#include "gamescreenlevel1.h"
#include <iostream>
#include "texture2d.h"
#include "collisions.h"
#include "powblock.h"

// The required parameters also need to be passed through the GameScreens constructor.
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) {
	m_level_map = nullptr;
	last_koopa_spawn = koopa_spawn_frequency;
	koopa_starting_direction = FACING_LEFT;
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
	
	for (int i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies[i];
	}
	m_enemies.clear();
}

void GameScreenLevel1::Render() {

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

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

	last_koopa_spawn -= deltaTime;
	if (last_koopa_spawn <= 0.0f) {

		last_koopa_spawn = koopa_spawn_frequency;

		if (koopa_starting_direction == FACING_LEFT) {
			CreateKoopa(Vector2D(SCREEN_WIDTH-32, 32), FACING_LEFT, KOOPA_SPEED);
			koopa_starting_direction = FACING_RIGHT;
		}
		else { 
			CreateKoopa(Vector2D(0, 32), FACING_RIGHT, KOOPA_SPEED);
			koopa_starting_direction = FACING_LEFT;
		}
		
	}

	//Update character
	mario_character->Update(deltaTime, e);
	luigi_character->Update(deltaTime, e);

	UpdatePOWBlock();

	UpdateEnemies(deltaTime, e);
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

	// Create Koopas
	CreateKoopa(Vector2D(150,32),FACING_RIGHT,KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

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

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e) {
	if (!m_enemies.empty()) {
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			// If enemy is on the bottom row of level tiles.
			if (m_enemies[i]->GetPosition().y > 300.0f) {
				// Enemy is off-screen horizontally.
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || 
				m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f)) {
					m_enemies[i]->SetAlive(false);
				}
			}

			//Perform actual update
			m_enemies[i]->Update(deltaTime, e);

			//Check for enemy-to-player collision
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && 
				(m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//Ignore collisions; behind level pipe.
			}
			else {
				if (Collisions::Instance()->Circle(m_enemies[i],mario_character)) {
					if (m_enemies[i]->GetInjured()) {
						m_enemies[i]->SetAlive(false);
					}
					else {
						//TODO: Kill Mario/Luigi
					}
				}
			}

			// Flag/Schedule for deletion if no longer alive
			if (!m_enemies[i]->GetAlive()) {
				enemyIndexToDelete = i;
			}

		}

		if (enemyIndexToDelete != -1) {
			delete m_enemies[enemyIndexToDelete];
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed) {
	CharacterKoopa* koopa = new CharacterKoopa(m_renderer,"Images/Koopa.png",position,m_level_map,direction,speed);
	m_enemies.push_back(koopa);
}