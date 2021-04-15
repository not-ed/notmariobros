#include "character.h"

Character::Character(SDL_Renderer* game_renderer, Vector2D start_position, LevelMap* map)
{
	renderer = game_renderer;
	position = start_position;

	facingDirection = FACING::FACING_RIGHT;

	movingLeft = false;
	movingRight = false;

	collisionRadius = 15.0f;

	currentLevelMap = map;

	alive = true;
}

Character::~Character()
{
	// This only needs to be set to null as it would have been holding the renderer PASSED IN when it was constructed.
	renderer = nullptr;
}

void Character::Update(float delta_time, SDL_Event e) {
	//Update Central X and Foot Positions 
	centralXPosition = (int)(position.x + ((anim.GetFrameWidth() * .5f))) / TILE_WIDTH;
	footPosition = (int)(position.y + anim.GetFrameHeight()) / TILE_HEIGHT;

	if (jumping) {
		// Decrease jump force over time if jumping to simulate gravity
		position.y -= jumpForce * delta_time;
		jumpForce -= JUMP_FORCE_DECREMENT * delta_time;

		if (jumpForce <= 0.0f) {
			jumping = false;
		}
	}

	// If the character is completely inside the level bounds and not stood on a map tile, then add gravity.
	// Dead characters should continue to fall until off-screen and not consider collision at all.
	// If a character is not jumping, but also not in level bounds, then they should not be obeying gravity briefly, lest they get stuck in a tile's floor.
	if(InLevelBounds() && currentLevelMap->GetTileAt(footPosition,centralXPosition) == 0 || !alive || (!InLevelBounds() && jumping)){
		AddGravity(delta_time);
		canJump = false;
	}
	else {
		canJump = true;
	}

	if (movingLeft)
	{
		bool wont_hit_wall = currentLevelMap->GetTileAt((position.y + anim.GetFrameHeight() - 1) / TILE_HEIGHT, (position.x - (movementSpeed * delta_time)) / TILE_WIDTH) == 0;
		// Stop a character from moving into a wall when they're not supposed to and get stuck and can't get out on their own.
		if (wont_hit_wall || jumping)
		{
			MoveLeft(delta_time);
		}
		
	}
	else if (movingRight)
	{
		bool wont_hit_wall = currentLevelMap->GetTileAt((position.y + anim.GetFrameHeight() - 1) / TILE_HEIGHT, (position.x + anim.GetFrameWidth() + (movementSpeed * delta_time)) / TILE_WIDTH) == 0;
		// Stop a character from moving into a wall when they're not supposed to and get stuck and can't get out on their own.
		if (wont_hit_wall || jumping)
		{
			MoveRight(delta_time);
		}
	}

	// Shift character upwards if they are stuck inside the floor for whatever reason, such as awkward jump heights, being stunned between level bounds etc.
	if (!jumping && canJump)
	{
		// stuck in floor
		if (currentLevelMap->GetTileAt((position.y + anim.GetFrameHeight() - 1) / TILE_HEIGHT, centralXPosition) == 1)
		{
			position.y -= 1;
		}
	}
}

void Character::SetPosition(Vector2D new_position) {
	position = new_position;
}

Vector2D Character::GetPosition() {
	return position;
}

void Character::MoveLeft(float delta_time) {
	facingDirection = FACING::FACING_LEFT;
	position.x -= delta_time * movementSpeed;
}

void Character::MoveRight(float delta_time) {
	facingDirection = FACING::FACING_RIGHT;
	position.x += delta_time * movementSpeed;
}

void Character::AddGravity(float delta_time) {
	// If the character is below the lowest floor of the screen when gravity is applied and still alive, then we cannot move them down further, otherwise they will go off-screen.
	// This is fine if the character is dead, as the intended effect is to allow them to fall out of the screen's view.
	if (position.y + 64 < SCREEN_HEIGHT || !alive) {
		position.y += GRAVITY * delta_time;
	}
	else {
		canJump = true;
	}
}

void Character::Jump(float force) {
	if (!jumping) {
		jumpForce = force;
		jumping = true;
		canJump = false;
	}
}

float Character::GetCollisionRadius() {
	return collisionRadius;
}

void Character::CancelJump() {
	jumping = false;
	jumpForce = 0;
}

void Character::SetAlive(bool is_alive) {
	if (alive && !is_alive)
	{
		OnKill();
	}
	alive = is_alive;
}

void Character::OnKill() {
	Jump(KILL_JUMP_FORCE);
}

bool Character::InLevelBounds() {
	Rect2D col = GetCollisionBox();
	//Over bounds on Left side
	if (position.x < 0)
	{
		return false;
	}
	// Over bounds of right side
	if (position.x+col.width > SCREEN_WIDTH)
	{
		return false;
	}

	return true;
}