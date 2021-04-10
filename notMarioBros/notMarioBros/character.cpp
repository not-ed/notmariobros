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

	//TODO: this does not need to be 2 boolean variables, this can be tied to an axis multiplier
	if (movingLeft)
	{
		MoveLeft(delta_time);
	}
	else if (movingRight)
	{
		MoveRight(delta_time);
	}

}

void Character::SetPosition(Vector2D new_position) {
	position = new_position;
}

Vector2D Character::GetPosition() {
	return position;
}

//TODO: These 2 functions do not need to be seperate just to change direction, this can be done via an axis multiplier.
void Character::MoveLeft(float delta_time) {
	facingDirection = FACING::FACING_LEFT;
	position.x -= delta_time * movementSpeed;
}

void Character::MoveRight(float delta_time) {
	facingDirection = FACING::FACING_RIGHT;
	float prev_x = position.x;
	position.x += delta_time * movementSpeed;
}
//

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
		SoundManager::Instance()->PlaySound(SOUND::ID::PLAYER_JUMP);
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

void Character::Debug_RenderHitbox() {
	/*Rect2D r = GetCollisionBox();
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 128);
	SDL_RenderDrawRect(m_renderer, new SDL_Rect{ (int)r.x,(int)r.y,(int)r.width,(int)r.height });

	int central_x = (int)(m_position.x + ((anim.GetFrameWidth() * .5f)));
	int foot_position = (int)(m_position.y + m_texture->GetHeight());
	SDL_SetRenderDrawColor(m_renderer, 0, 255, 255, 255);
	
	SDL_RenderDrawRect(m_renderer, new SDL_Rect{ central_x - 1,foot_position - 1,2,2 });

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);*/
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