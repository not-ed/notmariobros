#include "character.h"
#include "soundmanager.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map)
{
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imagePath)) {
		cerr << "[!] Failed to load character texture from '" << imagePath << "'." << endl;
	}

	m_facing_direction = FACING::FACING_RIGHT;

	m_moving_left = false;
	m_moving_right = false;

	m_collision_radius = 15.0f;

	m_current_level_map = map;

	m_alive = true;
}

Character::~Character()
{
	// This only needs to be set to null as it would have been holding the renderer PASSED IN when it was constructed.
	m_renderer = nullptr;

	delete m_texture;
	m_texture = nullptr;
}

void Character::Render() {
	if (m_facing_direction == FACING::FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else {
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e) {
	//Collision position
	int centralX_position = (int)(m_position.x + ((anim.GetFrameWidth() * .5f))) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;

	if (m_jumping) {
		m_position.y -= m_jump_force * deltaTime;
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		if (m_jump_force <= 0.0f) {
			m_jumping = false;
		}
	}

	if(m_current_level_map->GetTileAt(foot_position,centralX_position) == 0 || !m_alive){
		AddGravity(deltaTime);

		// This is a bit hacky, if this starts causing problems then a different approach to jumping will need to be considered later on.
		m_can_jump = false;
	}
	else {
		m_can_jump = true;
	}

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

}

void Character::SetPosition(Vector2D new_position) {
	m_position = new_position;
}

Vector2D Character::GetPosition() {
	return m_position;
}

void Character::MoveLeft(float deltaTime) {
	m_facing_direction = FACING::FACING_LEFT;
	m_position.x -= deltaTime * m_movement_speed;
}

void Character::MoveRight(float deltaTime) {
	m_facing_direction = FACING::FACING_RIGHT;
	float prev_x = m_position.x;
	m_position.x += deltaTime * m_movement_speed;
}

void Character::AddGravity(float deltaTime) {
	if (m_position.y + 64 < SCREEN_HEIGHT || !m_alive) {
		m_position.y += GRAVITY * deltaTime;
	}
	else {
		m_can_jump = true;
	}
}

void Character::Jump(float force) {
	if (!m_jumping) {
		m_jump_force = force;
		m_jumping = true;
		m_can_jump = false;
		SoundManager::Instance()->PlaySound(SOUND::ID::PLAYER_JUMP);
	}
}

float Character::GetCollisionRadius() {
	return m_collision_radius;
}

void Character::CancelJump() {
	m_jumping = false;
	m_jump_force = 0;
}

void Character::SetAlive(bool isAlive) {
	m_alive = isAlive;
	if (!m_alive) {
		OnKill();
	}
}

void Character::OnKill() {
	Jump(KILL_JUMP_FORCE);
}

void Character::Debug_RenderHitbox() {
	Rect2D r = GetCollisionBox();
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 128);
	SDL_RenderDrawRect(m_renderer, new SDL_Rect{ (int)r.x,(int)r.y,(int)r.width,(int)r.height });

	int central_x = (int)(m_position.x + ((anim.GetFrameWidth() * .5f)));
	int foot_position = (int)(m_position.y + m_texture->GetHeight());
	SDL_SetRenderDrawColor(m_renderer, 0, 255, 255, 255);
	
	SDL_RenderDrawRect(m_renderer, new SDL_Rect{ central_x - 1,foot_position - 1,2,2 });

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
}