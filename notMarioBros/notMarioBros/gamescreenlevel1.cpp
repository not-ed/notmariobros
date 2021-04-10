#include "gamescreenlevel1.h"

// The required parameters also need to be passed through the GameScreens constructor.
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* game_renderer) : GameScreen(game_renderer) {
	levelMap = nullptr;
	// TODO: this should be removed as levels move towards using a manifest of enemies and not spawning them endlessly.
	last_koopa_spawn = koopa_spawn_frequency;
	koopa_starting_direction = FACING_LEFT;
	//
	SetUpLevel();
}


GameScreenLevel1::~GameScreenLevel1()
{
	delete backgroundTexture;
	backgroundTexture = nullptr;

	delete mario;
	mario = nullptr;

	delete luigi;
	luigi = nullptr;

	delete powBlock;
	powBlock = nullptr;
	
	for (int i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies[i];
	}

	m_enemies.clear();
}

void GameScreenLevel1::Render() {
	// Pointers to characters that are dead, so that they can be drawn last to appear at the end of the render loop.
	std::vector<Character*> dead_characters;

	// Render all enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->IsAlive()) {
			m_enemies[i]->Render();
		}
		else {
			// Put off rendering if dead until the end of the loop.
			dead_characters.push_back(m_enemies[i]); 
		}
	}

	//Render mario/luigi
	if (mario->IsAlive())
	{
		mario->Render();
	}
	else {
		dead_characters.push_back(mario);
	}
	
	// If game is actually being played 2P
	if (luigi != nullptr)
	{
		if (luigi->IsAlive())
		{
			luigi->Render();
		}
		else {
			dead_characters.push_back(luigi);
		}
	}

	powBlock->Render();

	backgroundTexture->Render(Vector2D(0, backgroundYPos), SDL_FLIP_NONE);
	
	// Render all dead characters now that everything has been drawn
	for (int i = 0; i < dead_characters.size(); i++)
	{
		dead_characters[i]->Render();
	}

	// The pointers of dead characters are shared, they do not need to be deleted here.
	dead_characters.clear();

	mario->RenderGUI();
	if (luigi != nullptr)
	{
		//luigi->RenderGUI(); TODO: This can be uncommented once luigi inheritence is set up
	}
}

void GameScreenLevel1::Update(float delta_time, SDL_Event e) {
	screenShakeTimer.Update(delta_time);

	// Screen shake (if applicable)
	if (!screenShakeTimer.IsExpired()) {
		accumulatedWobble++;
		backgroundYPos = sin(accumulatedWobble);
		backgroundYPos *= 8.0;
	}
	else {
		backgroundYPos = 0.0f;
	}
	
	// TODO: this should be removed as levels move towards using a manifest of enemies and not spawning them endlessly.
	last_koopa_spawn -= delta_time;
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
	//////////////////////////////

	//Update mario/luigi
	mario->Update(delta_time, e);
	QueryLevelBounds(mario);
	if (luigi != nullptr) {
		luigi->Update(delta_time, e);
		QueryLevelBounds(luigi);
	}

	UpdatePOWBlock();

	UpdateEnemies(delta_time, e);
}

bool GameScreenLevel1::SetUpLevel() {
	// Set up screen shake timer
	screenShakeTimer.SetTime(SHAKE_DURATION, false);

	// Load background texture
	backgroundTexture = new Texture2D(renderer);
	if (!backgroundTexture->LoadFromFile("Images/lvl1background.png"))
	{
		std::cerr << "[!] Failed to load background texture." << std::endl;
		return false;
	}

	// Establish level map data
	SetLevelMap();

	// Setting up player character
	mario = new CharacterMario(renderer, Vector2D(64, 330), levelMap);
	players[0] = mario;

	// TODO: This should be set up so that luigi is spawned when 2P is set.
	luigi = new CharacterLuigi(renderer, Vector2D(432, 330), levelMap);
	players[1] = nullptr;
	// Setting up POW block
	powBlock = new PowBlock(renderer, levelMap);
	//screenshakeIsActive = false;
	backgroundYPos = 0.0f;

	// Create Koopas
	// TODO: remove this later as levels move to manifesting
	CreateKoopa(Vector2D(150,32),FACING_RIGHT,KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	// Start playing level music
	SoundManager::Instance()->PlayMusic(MUSIC::ID::MARIO);

	return true;
}

void GameScreenLevel1::SetLevelMap() {
	// Establish tile/collision data.
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
	if (levelMap != nullptr) {
		delete levelMap;
	}

	//Set new map
	levelMap = new LevelMap(map);
}

void GameScreenLevel1::UpdatePOWBlock() {
	for (int i = 0; i < 2; i++)
	{
		if (players[i] != nullptr)
		{
			if (Collisions::Instance()->Box(powBlock->GetCollisionBox(), players[i]->GetHeadHitBox()) && powBlock->IsAvailable())
			{
				// Player collided with a usable POW block while jumping up
				if (players[i]->IsJumping()) {
					DoScreenShake();

					powBlock->TakeHit();

					players[i]->CancelJump();
				}
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake() {
	// Restart the screen shake timer and any accumulated wobble from the last shake.
	screenShakeTimer.Reset();
	accumulatedWobble = 0.0f;

	// Damage/stun all on-screen enemies
	// TODO: this should only be done to enemies that are activated.
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float delta_time, SDL_Event e) {
	// If there is no enemies to start with, none of this needs to be done
	if (!m_enemies.empty()) {
		

		// Keep track of the next index (if any) of any enemies that need to be deleted after the loop
		int enemyIndexToDelete = -1;

		for (int i = 0; i < m_enemies.size(); i++)
		{
			// Check if going off screen, and wrap accordingly if needed.
			QueryLevelBounds(m_enemies[i]);

			m_enemies[i]->Update(delta_time, e);

			// For each player
			for (int j = 0; j < 2; j++)
			{
				if (players[j] != nullptr)
				{
					// Check for enemy-to-player collision
					if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) &&
						(m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
					{
						// Ignore collisions; behind level pipe.
					}
					else if (players[j]->IsAlive()) {

						if (players[j]->IsJumping()) {
							// If player head hitbox has hit an enemy while jumping
							if ((!m_enemies[i]->GetInjured()) && (Collisions::Instance()->Box(m_enemies[i]->GetCollisionBox(), players[j]->GetHeadHitBox())))
							{
								m_enemies[i]->TakeDamage();

								SoundManager::Instance()->PlaySound(SOUND::ID::ENEMY_HURT);

								players[j]->CancelJump();
							}
						}
						/*else*/ if (Collisions::Instance()->Box(m_enemies[i]->GetCollisionBox(), players[j]->GetCollisionBox())) { // Player has collided with an enemy while on the ground
							// If the enemy is stunned/injured and still alive, kill it
							if (m_enemies[i]->GetInjured()) {

								if (m_enemies[i]->IsAlive()) {

									m_enemies[i]->SetAlive(false);

								}
							}
							else { // The enemy is not stunned
								// If the player is not invincible, kill them.
								if (!players[j]->Invincible()) {

									players[j]->SetAlive(false);

								}
							}
						}
					}
				}
			}

			// Flag/Schedule for deletion if no longer alive and off screen
			if (!m_enemies[i]->IsAlive() && m_enemies[i]->GetPosition().y > SCREEN_HEIGHT) {
				enemyIndexToDelete = i;
			}

		}

		// If an enemy index to delete has been given, then delete it.
		if (enemyIndexToDelete != -1) {

			delete m_enemies[enemyIndexToDelete];

			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed) {
	CharacterKoopa* koopa = new CharacterKoopa(renderer,position, levelMap,direction,speed);
	m_enemies.push_back(koopa);
}

void GameScreenLevel1::QueryLevelBounds(Character* chara) {
	// Get a temporary copy of the characters position and their hitbox
	Vector2D char_pos = chara->GetPosition();
	Rect2D char_col = chara->GetCollisionBox();

	// Set up a flag if the player has had to be flipped around to the other side of the screen on the x-axis
	bool flipped = false;

	if ((char_pos.x) > SCREEN_WIDTH) //off bounds on the right side
	{
		// Flip to the left side
		char_pos.x = -(char_col.width) + 1;
		flipped = true;
	}
	else if ((char_pos.x + char_col.width) < 0){ //off bounds on the left side
		// Flip to the right side
		char_pos.x = SCREEN_WIDTH - 1;
		flipped = true;
	}

	if (flipped)
	{
		// If inside a pipe, wrap around vertically as well to come out the other end of a pipe at the top/bottom of the screen.
		if ((chara->GetPosition().y > 300.0f || chara->GetPosition().y <= 64.0f) || (chara->GetPosition().x < 64.0f || chara->GetPosition().x > SCREEN_WIDTH - 96.0f)){
			if (chara->GetPosition().y > 300.0f) // Upper area to lower area
			{
				char_pos.y -= (321.0f);
				chara->TriggerPipeFlag();
			}
			else if (chara->GetPosition().y <= 64.0f){ // Lower area to upper area
				char_pos.y += (321.0f);
				chara->TriggerPipeFlag();
			}
		}
	}
	
	chara->SetPosition(char_pos);
}