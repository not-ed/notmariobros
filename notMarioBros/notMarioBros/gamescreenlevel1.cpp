#include "gamescreenlevel1.h"

// The required parameters also need to be passed through the GameScreens constructor.
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* game_renderer, ScoreCounter* score_counter) : GameScreen(game_renderer,score_counter) {
	levelMap = nullptr;
	// TODO: this should be removed as levels move towards using a manifest of enemies and not spawning them endlessly.
	last_koopa_spawn = koopa_spawn_frequency;
	koopa_starting_direction = FACING_LEFT;
	//

	scoreNameWindow.SetRenderer(game_renderer);

	gameOverTimer.SetTime(GAME_OVER_TIME, false);

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

void GameScreenLevel1::Render() {
	// Pointers to characters that are dead, so that they can be drawn last to appear at the end of the render loop.
	std::vector<Character*> dead_characters;


	// Render all enemies
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->IsAlive()) {
			enemies[i]->Render();
		}
		else {
			// Put off rendering if dead until the end of the loop.
			dead_characters.push_back(enemies[i]); 
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

	//Render fireballs
	for (int i = 0; i < fireballs.size(); i++)
	{
		fireballs[i]->Render();
	}

	mario->RenderGUI();
	if (luigi != nullptr)
	{
		luigi->RenderGUI();
	}

	// Draw Score
	Text::Draw(to_string(scoreCounter->GetCurrentScore()), IntVector2D(SCREEN_WIDTH/2, SCREEN_HEIGHT - 24), FONT::ID::REGULAR, FONT::ALLIGNMENT::CENTER);

	// Draw remaining enemy counters
	Text::Draw(to_string(enemies.size()), IntVector2D(32, 24), FONT::ID::REGULAR, FONT::ALLIGNMENT::CENTER);
	Text::Draw(to_string(enemies.size()), IntVector2D(SCREEN_WIDTH - 32, 24), FONT::ID::REGULAR, FONT::ALLIGNMENT::CENTER);

	// The game over sequence is being displayed
	if (!gameOverTimer.IsExpired())
	{
		Text::Draw("GAME OVER", IntVector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), FONT::ID::REGULAR, FONT::ALLIGNMENT::CENTER);
	}

	// Display the high score name entry window if it is being used.
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
		return; // Return early, if this or the high score screen is being shown, the game doesn't need to update, only be drawn.
	}

	if (scoreNameWindow.IsDisplayed())
	{
		scoreNameWindow.Update(delta_time, e);

		// Window has been closed by the player, meaning they've submitted a name and score, we can now return to the main menu
		if (!scoreNameWindow.IsDisplayed())
		{
			HighScore::SubmitScoreEntry(scoreNameWindow.GetEnteredName().c_str(), scoreCounter->GetCurrentScore());
			RequestScreenSwitch(SCREEN_MENU);
		}
		return; // Return early, if this or the game over screen is being shown, the game doesn't need to update, only be drawn.
	}
	
	// Neither screen is being shown.
	{

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
				CreateKoopa(Vector2D(SCREEN_WIDTH - 32, 32), FACING_LEFT);
				koopa_starting_direction = FACING_RIGHT;
			}
			else {
				CreateKoopa(Vector2D(0, 32), FACING_RIGHT);
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

	// Setting up player characters
	mario = new CharacterMario(renderer, Vector2D(64, 330), levelMap);
	players[0] = mario;
	// As this is the first level of any run, lives can be reset here.
	mario->ResetLives();

	//if luigi
	

	// TODO: This should be set up so that luigi is spawned when 2P is set.
	luigi = new CharacterLuigi(renderer, Vector2D(416, 330), levelMap);
	players[1] = luigi;
	// Setting up POW block
	powBlock = new PowBlock(renderer, levelMap);
	//screenshakeIsActive = false;
	backgroundYPos = 0.0f;

	luigi->ResetLives();

	// Create Koopas
	// TODO: remove this later as levels move to manifesting
	CreateKoopa(Vector2D(150,32),FACING_RIGHT);
	//CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	CreateIcicle(Vector2D(325, 32), FACING_LEFT);
	CreateCrab(Vector2D(SCREEN_WIDTH/2,32), FACING_RIGHT);
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

void GameScreenLevel1::DoScreenShake() {
	// Restart the screen shake timer and any accumulated wobble from the last shake.
	screenShakeTimer.Reset();
	accumulatedWobble = 0.0f;

	// Damage/stun all on-screen enemies
	// TODO: this should only be done to enemies that are activated.
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->TakeDamage();

		QueryIcicleInjury(enemies[i]);

		scoreCounter->Add(SCORE_POW_BLOCK_STUN);
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
	// If there is no enemies to start with, none of this needs to be done

	if (!enemies.empty()) {
		
		// Keep track of the next index (if any) of any enemies that need to be deleted after the loop
		int enemyIndexToDelete = -1;

		for (int i = 0; i < enemies.size(); i++)
		{
			// Check if going off screen, and wrap accordingly if needed.
			QueryLevelBounds(enemies[i]);

			enemies[i]->Update(delta_time, e);

			// If the enemy is a crab, request any held fireballs if they have them.
			if (enemies[i]->GetEnemyType() == ENEMY_TYPE::CRAB)
			{
				CharacterCrab* crab = (CharacterCrab*)enemies[i];
				while (crab->HoldingFireballs())
				{
					fireballs.push_back(crab->FetchFireball());
				}
			}


			// For each player
			for (int j = 0; j < 2; j++)
			{
				if (players[j] != nullptr)
				{
					// Check for enemy-to-player collision
					if ((enemies[i]->GetPosition().y > 300.0f || enemies[i]->GetPosition().y <= 64.0f) &&
						(enemies[i]->GetPosition().x < 64.0f || enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
					{
						// Ignore collisions; behind level pipe.
					}
					else if (players[j]->IsAlive()) {

						if (players[j]->IsJumping()) {
							// If player head hitbox has hit an enemy while jumping
							if ((!enemies[i]->GetInjured()) && (Collisions::Instance()->Box(enemies[i]->GetCollisionBox(), players[j]->GetHeadHitBox())))
							{
								enemies[i]->TakeDamage();

								SoundManager::Instance()->PlaySound(SOUND::ID::ENEMY_HURT);

								players[j]->CancelJump();

								QueryIcicleInjury(enemies[i]);

								// Award double points if the enemy is angry
								scoreCounter->Add(SCORE_ENEMY_STUNNED,1 + enemies[i]->IsAngry());
							}
						}
						/*else*/ if (Collisions::Instance()->Box(enemies[i]->GetCollisionBox(), players[j]->GetCollisionBox())) { // Player has collided with an enemy while on the ground
							// If the enemy is stunned/injured and still alive, kill it
							if (enemies[i]->GetInjured()) {

								if (enemies[i]->IsAlive()) {
									//Kill the enemy
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

		if (coins[i]->Expired()) // Coin hasn't been picked up in time and needs to vanish
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

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction) {
	CharacterKoopa* koopa = new CharacterKoopa(renderer,position, levelMap,direction);
	enemies.push_back(koopa);
}

void GameScreenLevel1::CreateCrab(Vector2D position, FACING direction) {
	CharacterCrab* crab = new CharacterCrab(renderer, position, levelMap, direction);
	enemies.push_back(crab);
}

void GameScreenLevel1::CreateIcicle(Vector2D position, FACING direction) {
	CharacterIcicle* icicle = new CharacterIcicle(renderer, position, levelMap, direction);
	enemies.push_back(icicle);
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