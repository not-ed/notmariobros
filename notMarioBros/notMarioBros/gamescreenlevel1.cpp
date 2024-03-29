#include "gamescreenlevel1.h"

// The required parameters also need to be passed through the GameScreens constructor.
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* game_renderer, ScoreCounter* score_counter, bool include_luigi) : GameScreen(game_renderer,score_counter) {
	
	scoreNameWindow.SetRenderer(game_renderer);

	isTwoPlayer = include_luigi;

	levelMap = nullptr;
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
	
	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}

	for (int i = 0; i < coins.size(); i++)
	{
		delete coins[i];
	}

	for (int i = 0; i < fireballs.size(); i++)
	{
		delete fireballs[i];
	}
	
	enemies.clear();
	coins.clear();
	fireballs.clear();
}

bool GameScreenLevel1::SetUpLevel() {
	// Set up screen shake timer
	screenShakeTimer.SetTime(SHAKE_DURATION, false);

	// Load one-off background texture
	backgroundTexture = new Texture2D(renderer);
	if (!backgroundTexture->LoadFromFile("Images/lvl1background.png"))
	{
		std::cerr << "[!] Failed to load background texture." << std::endl;
		return false;
	}

	// Establish level map data
	SetLevelMap();

	// Setting up player characters
	mario = new CharacterMario(renderer, Vector2D(64, 330), levelMap);
	players[0] = mario;
	mario->ResetLives();
	// Set up Luigi if the game is being played 2P
	if (isTwoPlayer)
	{
		luigi = new CharacterLuigi(renderer, Vector2D(416, 330), levelMap);
		players[1] = luigi;
		luigi->ResetLives();
	}

	// Setting up POW block
	powBlock = new PowBlock(renderer, levelMap);
	backgroundYPos = 0.0f;

	// Set initial times for dictating enemy spawns
	koopaSpawnTimer.SetTime(2.0f + fmod(rand(), KOOPA_SPAWN_TIME_MAX - 2.0f), true);
	crabSpawnTimer.SetTime(10.0f + fmod(rand(), CRAB_SPAWN_TIME_MAX - 10.0f), true);
	icicleSpawnTimer.SetTime(20.0f + fmod(rand(), ICICLE_SPAWN_TIME_MAX - 20.0f), true);

	// Set up how long the game over screen will be displayed at the end of the game.
	gameOverTimer.SetTime(GAME_OVER_TIME, false);

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

	// Clean up any old maps if they exist
	if (levelMap != nullptr) {
		delete levelMap;
	}

	//Set new map
	levelMap = new LevelMap(map);
}

void GameScreenLevel1::Render() {
	// Pointers to characters that are dead, so that they can be drawn last at the end of the render loop in order to guarantee they are in front of everything.
	std::vector<Character*> dead_characters;

	// Render enemies
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsActivated())
		{
			if (enemies[i]->IsAlive()) {
				enemies[i]->Render();
			}
			else {
				// Put off rendering if dead until the end of the loop.
				dead_characters.push_back(enemies[i]);
			}
		}
	}

	// Render Coins
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->Render();
	}

	//Render mario/luigi
	if (mario->IsAlive())
	{
		mario->Render();
	}
	else {
		dead_characters.push_back(mario);
	}
	// Is game being played 2P?
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

	// The pointers of dead characters are shared, they do not need to be deleted directly, and so the vector can just be cleared.
	dead_characters.clear();

	//Render fireballs
	for (int i = 0; i < fireballs.size(); i++)
	{
		fireballs[i]->Render();
	}

	// Render any GUI elements from Mario and Luigi
	mario->RenderGUI();
	if (luigi != nullptr)
	{
		luigi->RenderGUI();
	}

	// Draw Score counter
	Text::Draw(to_string(scoreCounter->GetCurrentScore()), IntVector2D(SCREEN_WIDTH/2, SCREEN_HEIGHT - 24), FONT::ID::REGULAR, FONT::ALLIGNMENT::CENTER);

	// Display game over sequence if needed
	if (!gameOverTimer.IsExpired())
	{
		Text::Draw("GAME OVER", IntVector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), FONT::ID::REGULAR, FONT::ALLIGNMENT::CENTER);
	}

	// Display the high score name entry window if needed
	if (scoreNameWindow.IsDisplayed())
	{
		scoreNameWindow.Render();
	}
}

void GameScreenLevel1::Update(float delta_time, SDL_Event e) {
	// The game over screen is being displayed, so game logic does not need to be updated.
	if (!gameOverTimer.IsExpired())
	{
		gameOverTimer.Update(delta_time);

		// If the last update has ran out the game over timer, display the high score menu if needed and then return to main menu.
		if (gameOverTimer.IsExpired())
		{
			// Check if a highscore is eligible for addition to the high score table, if it is, call the score name window before returning to the main menu.
			if (HighScore::NewScoreAchieved(scoreCounter->GetCurrentScore()))
			{
				SoundManager::Instance()->StopMusic();
				SoundManager::Instance()->PlaySound(SOUND::ID::NEW_HIGH_SCORE);
				scoreNameWindow.Display();
			}
			else {
				RequestScreenSwitch(SCREEN_MENU);
			}
		}
		return; // Return early, if this or the high score screen is being shown, the game doesn't need to update, only be drawn in whatever state it was in.
	}

	// High score entry window is being displayed, so game logic 
	if (scoreNameWindow.IsDisplayed())
	{
		scoreNameWindow.Update(delta_time, e);

		// Window has been closed by the player, meaning they've submitted a name and score, we can now return to the main menu
		if (!scoreNameWindow.IsDisplayed())
		{
			HighScore::SubmitScoreEntry(scoreNameWindow.GetEnteredName().c_str(), scoreCounter->GetCurrentScore());

			RequestScreenSwitch(SCREEN_MENU);
		}
		return; // Return early, if this or the game over screen is being shown, the game doesn't need to update, only be drawn in whatever state it was in.
	}
	
	// If neither screen is being shown. We can continue with the update loop as normal

	// Screen shake (if applicable)
	screenShakeTimer.Update(delta_time);
	if (!screenShakeTimer.IsExpired()) {
		accumulatedWobble++;
		backgroundYPos = sin(accumulatedWobble);
		backgroundYPos *= 8.0;
	}
	else {
		backgroundYPos = 0.0f;
	}

	//Update mario/luigi
	mario->Update(delta_time, e);
	QueryLevelBounds(mario);

	if (luigi != nullptr) {
		luigi->Update(delta_time, e);
		QueryLevelBounds(luigi);
	}

	UpdatePOWBlock();

	UpdateEnemies(delta_time, e);

	UpdateCoins(delta_time, e);

	UpdateFireBalls(delta_time, e);

	//Check if game is over
	if (mario->OutOfGame() && (luigi == nullptr || luigi->OutOfGame()))
	{
		if (gameOverTimer.IsExpired())
		{
			gameOverTimer.Reset();
		}
	}
}

void GameScreenLevel1::DoScreenShake() {
	// Restart the screen shake timer and any accumulated wobble from the last shake.
	screenShakeTimer.Reset();
	accumulatedWobble = 0.0f;

	// Damage/stun all on-screen enemies that are "activated"
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsActivated())
		{
			enemies[i]->TakeDamage();

			QueryIcicleInjury(enemies[i]);

			scoreCounter->Add(SCORE_POW_BLOCK_STUN);
		}
	}
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

void GameScreenLevel1::UpdateEnemies(float delta_time, SDL_Event e) {

	koopaSpawnTimer.Update(delta_time);
	crabSpawnTimer.Update(delta_time);
	icicleSpawnTimer.Update(delta_time);

	// Spawn a random number of koopas if needed
	if (koopaSpawnTimer.IsExpired())
	{
		// How many koopas to spawn this time around
		int koopa_count = rand() % 5;
		for (int i = 0; i < koopa_count; i++)
		{
			if (i % 2 == 0)
			{
				CreateKoopa(Vector2D(SCREEN_WIDTH - 64, 32), FACING_LEFT, 1.0f * (fmod(rand(),5.0f) * i));
			}
			else {
				CreateKoopa(Vector2D(32, 32), FACING_RIGHT, 1.0f * (fmod(rand(), 5.0f) * i));
			}
		}
		// Set a new random spawn time and reset the timer.
		koopaSpawnTimer.SetTime(2.0f + fmod(rand(), KOOPA_SPAWN_TIME_MAX - 2.0f), true);
	}

	// Spawn a random number of crabs if needed
	if (crabSpawnTimer.IsExpired())
	{
		// How many koopas to spawn this time around
		int crab_count = rand() % 3;
		for (int i = 0; i < crab_count; i++)
		{
			if (i % 2 == 0)
			{
				CreateCrab(Vector2D(SCREEN_WIDTH - 64, 32), FACING_LEFT, 1.0f * (fmod(rand(), 10.0f) * i));
			}
			else {
				CreateCrab(Vector2D(32, 32), FACING_RIGHT, 1.0f * (fmod(rand(), 10.0f) * i));
			}
		}
		// Set a new random spawn time and reset the timer.
		crabSpawnTimer.SetTime(10.0f + fmod(rand(), KOOPA_SPAWN_TIME_MAX - 10.0f), true);
	}

	if (icicleSpawnTimer.IsExpired())
	{
		int spawn_side = rand() % 2;

		if (spawn_side == 0)
		{
			CreateIcicle(Vector2D(SCREEN_WIDTH - 64, 32), FACING_LEFT, 1.0f * (fmod(rand(), 23.0f)));
		}
		else {
			CreateIcicle(Vector2D(32, 32), FACING_RIGHT, 1.0f * (fmod(rand(), 23.0f)));
		}

		// Set a new random spawn time and reset the timer.
		icicleSpawnTimer.SetTime(20.0f + fmod(rand(), KOOPA_SPAWN_TIME_MAX - 20.0f), true);
	}

	// If there is no enemies actually in the level, no updating needs to be done.
	if (!enemies.empty()) {
		
		// Keep track of the next index (if any) of any enemies that need to be deleted after the loop
		int enemyIndexToDelete = -1;

		for (int i = 0; i < enemies.size(); i++)
		{
			// Check if going off screen, and wrap accordingly if needed.
			QueryLevelBounds(enemies[i]);

			// Enemies that are not activated still need to be updated, otherwise their activation timer will never count down
			enemies[i]->Update(delta_time, e);

			// If the enemy is a crab, request any held fireball pointers if they have them.
			if (enemies[i]->GetEnemyType() == ENEMY_TYPE::CRAB)
			{
				CharacterCrab* crab = (CharacterCrab*)enemies[i];
				while (crab->HoldingFireballs())
				{
					fireballs.push_back(crab->FetchFireball());
				}
			}

			// If an enemy is not yet activated, then all interaction with the player should be ignored.
			if (enemies[i]->IsActivated()) {
				// For each player
				for (int j = 0; j < 2; j++)
				{
					if (players[j] != nullptr)
					{
						// Collisions between the player and enemies should be ignored if they are behind and "entering" a level pipe
						bool behind_level_pipe = (enemies[i]->GetPosition().y > 300.0f || enemies[i]->GetPosition().y <= 64.0f) && (enemies[i]->GetPosition().x < 64.0f || enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f);

						if (players[j]->IsAlive() && !behind_level_pipe) {

							if (players[j]->IsJumping()) {
								// If player head hitbox has hit an enemy while jumping
								if ((!enemies[i]->GetInjured()) && (Collisions::Instance()->Box(enemies[i]->GetCollisionBox(), players[j]->GetHeadHitBox())))
								{
									enemies[i]->TakeDamage();

									SoundManager::Instance()->PlaySound(SOUND::ID::ENEMY_HURT);

									players[j]->CancelJump();

									QueryIcicleInjury(enemies[i]);

									// Award double points if the enemy is angry
									scoreCounter->Add(SCORE_ENEMY_STUNNED, 1 + enemies[i]->IsAngry());
								}
							}

							// Player has collided with an enemy
							if (Collisions::Instance()->Box(enemies[i]->GetCollisionBox(), players[j]->GetCollisionBox())) {
								// If the enemy is stunned/injured and still alive, kill it
								if (enemies[i]->GetInjured()) {

									if (enemies[i]->IsAlive()) {

										enemies[i]->SetAlive(false);

										// Award score based on the type of enemy killed, and double it if they were angry
										switch (enemies[i]->GetEnemyType())
										{
										case ENEMY_TYPE::KOOPA:
											scoreCounter->Add(SCORE_KOOPA_KILLED, 1 + enemies[i]->IsAngry());
											break;
										case ENEMY_TYPE::CRAB:
											scoreCounter->Add(SCORE_CRAB_KILLED, 1 + enemies[i]->IsAngry());
											break;
										default:
											break;
										}
									}
								}
								else { // The enemy is not stunned, meaning the player should be killed.

									// If the player is not invincible, kill them.
									if (!players[j]->Invincible()) {

										players[j]->SetAlive(false);

									}
								}
							}
						}
					}
				}
			}

			// Flag/Schedule for deletion if no longer alive and off screen
			if (!enemies[i]->IsAlive() && enemies[i]->GetPosition().y > SCREEN_HEIGHT) {
				enemyIndexToDelete = i;
			}

		}

		// If an enemy index to delete has been given, then delete it.
		if (enemyIndexToDelete != -1) {

			delete enemies[enemyIndexToDelete];

			enemies.erase(enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::UpdateCoins(float delta_time, SDL_Event e) {
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->Update(delta_time, e);

		// Coin hasn't been picked up in time and needs to vanish
		if (coins[i]->Expired()) 
		{
			delete coins[i];
			coins.erase(coins.begin() + i);
		}
		else {
			for (int j = 0; j < 2; j++)
			{
				if (players[j] != nullptr)
				{
					// If an alive player has collided with a coin
					if (Collisions::Instance()->Circle(coins[i], players[j]) && players[j]->IsAlive())
					{
						delete coins[i];
						coins.erase(coins.begin() + i);
						SoundManager::Instance()->PlaySound(SOUND::ID::COIN);
						scoreCounter->Add(SCORE_COIN_COLLECTED);
						break;
					}
				}
			}
		}
	}
}

void GameScreenLevel1::UpdateFireBalls(float delta_time, SDL_Event e) {
	for (int i = 0; i < fireballs.size(); i++)
	{
		fireballs[i]->Update(delta_time, e);

		for (int j = 0; j < 2; j++)
		{
			if (players[j] != nullptr)
			{
				// Kill any players that collide with a fireball.
				if (Collisions::Instance()->Box(fireballs[i]->GetCollisionBox(), players[j]->GetCollisionBox()) && players[j]->IsAlive() && !players[j]->Invincible()) {
					players[j]->SetAlive(false);
				}
			}
		}
		// Destroy any fire balls that have gone off screen
		if (fireballs[i]->GetPosition().y > SCREEN_HEIGHT)
		{
			delete fireballs[i];
			fireballs.erase(fireballs.begin() + i);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float activation_time) {
	CharacterKoopa* koopa = new CharacterKoopa(renderer,position, levelMap,direction,activation_time);
	enemies.push_back(koopa);
}

void GameScreenLevel1::CreateCrab(Vector2D position, FACING direction, float activation_time) {
	CharacterCrab* crab = new CharacterCrab(renderer, position, levelMap, direction,activation_time);
	enemies.push_back(crab);
}

void GameScreenLevel1::CreateIcicle(Vector2D position, FACING direction, float activation_time) {
	CharacterIcicle* icicle = new CharacterIcicle(renderer, position, levelMap, direction,activation_time);
	enemies.push_back(icicle);
}

void GameScreenLevel1::QueryLevelBounds(Character* chara) {
	// Get a temporary copy of the character's position and their hitbox for reference/modification
	Vector2D char_pos = chara->GetPosition();
	Rect2D char_col = chara->GetCollisionBox();

	// Set up a flag for if the player has had to be flipped around to the other side of the screen on the x-axis
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
				char_pos.y += (320.0f);
				chara->TriggerPipeFlag();
			}
		}
	}
	
	chara->SetPosition(char_pos);
}

void GameScreenLevel1::QueryIcicleInjury(CharacterKoopa* enemy) {
	// Injured enemy is an Incicle
	if (enemy->GetEnemyType() == ENEMY_TYPE::ICICLE)
	{
		// Icicles are killed instantly upon being injured, but drop multiple coins before doing so, which needs to be tracked by the game screen.
		CharacterIcicle* icicle = (CharacterIcicle*)enemy;
		for (int i = 0; i < icicle->GetCoinDropAmount(); i++)
		{
			coins.push_back(icicle->DropCoin());
		}
	}
}