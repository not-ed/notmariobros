#include "character.h"
#include "texture2d.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position)
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
	m_jumping = false;
	m_current_velocity = 0.0f;
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
	AddGravity(deltaTime);

	

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
	
	if (m_jumping) {
		Jump(deltaTime);
	}


	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_LEFT) {
			m_moving_left = true;
		}
		if (e.key.keysym.sym == SDLK_RIGHT) {
			m_moving_right = true;
		}
		if (e.key.keysym.sym == SDLK_UP) {
			m_jumping = true;
		}
		break;
	case SDL_KEYUP:
		if (e.key.keysym.sym == SDLK_LEFT) {
			m_moving_left = false;
		}
		if (e.key.keysym.sym == SDLK_RIGHT) {
			m_moving_right = false;
		}
		if (e.key.keysym.sym == SDLK_UP) {
			m_jumping = false;
		}
		break;
	default:
		break;
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
	m_position.x -= deltaTime * MOVEMENTSPEED;
}

void Character::MoveRight(float deltaTime) {
	m_facing_direction = FACING::FACING_RIGHT;
	m_position.x += deltaTime * MOVEMENTSPEED;
}

void Character::AddGravity(float deltaTime) {
	if (m_position.y + m_texture->GetHeight() < SCREEN_HEIGHT) { // On "Ground"
		m_current_velocity += GRAVITY_FORCE * deltaTime;
	}
	else {
		if (m_position.y + m_texture->GetHeight() > SCREEN_HEIGHT) {
			m_position.y = SCREEN_HEIGHT - m_texture->GetHeight();
			m_current_velocity = 0;
		}
	}
	m_position.y += m_current_velocity * deltaTime;
	cout << m_current_velocity << endl;
}

void Character::Jump(float deltaTime) {
	if (m_current_velocity == 0) {
		m_current_velocity = -JUMP_FORCE;
	}
	else {
		// Additonal negative velocity is add if the jump key is continued to be held down when jumping, allowing the player to control jump height to be higher if they hold the key down.
		m_current_velocity -= (JUMP_FORCE * .75f)* deltaTime;
	}
}
