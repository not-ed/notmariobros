#include "texturemanager.h"

TextureManager* TextureManager::m_instance = nullptr;

void TextureManager::LoadAssets(SDL_Renderer* renderer) {
	if (!initialized) {
		textures[TEXTURE::ID::POW_BLOCK] = new Texture2D(renderer);
		textures[TEXTURE::ID::POW_BLOCK]->LoadFromFile("Images/PowBlock.png");
		frameCount[TEXTURE::ID::POW_BLOCK] = 3;

		textures[TEXTURE::ID::FIREBALL] = new Texture2D(renderer);
		textures[TEXTURE::ID::FIREBALL]->LoadFromFile("Images/fireball.png");
		frameCount[TEXTURE::ID::FIREBALL] = 4;

		textures[TEXTURE::ID::MARIO_IDLE] = new Texture2D(renderer);
		textures[TEXTURE::ID::MARIO_IDLE]->LoadFromFile("Images/Mario.png");
		frameCount[TEXTURE::ID::MARIO_IDLE] = 1;

		textures[TEXTURE::ID::MARIO_RUN] = new Texture2D(renderer);
		textures[TEXTURE::ID::MARIO_RUN]->LoadFromFile("Images/mario_run.png");
		frameCount[TEXTURE::ID::MARIO_RUN] = 3;

		textures[TEXTURE::ID::MARIO_JUMP] = new Texture2D(renderer);
		textures[TEXTURE::ID::MARIO_JUMP]->LoadFromFile("Images/mario_jump.png");
		frameCount[TEXTURE::ID::MARIO_JUMP] = 1;

		textures[TEXTURE::ID::MARIO_DIE] = new Texture2D(renderer);
		textures[TEXTURE::ID::MARIO_DIE]->LoadFromFile("Images/mario_die.png");
		frameCount[TEXTURE::ID::MARIO_DIE] = 1;

		textures[TEXTURE::ID::LUIGI_IDLE] = new Texture2D(renderer);
		textures[TEXTURE::ID::LUIGI_IDLE]->LoadFromFile("Images/Luigi.png");
		frameCount[TEXTURE::ID::LUIGI_IDLE] = 1;

		textures[TEXTURE::ID::LUIGI_RUN] = new Texture2D(renderer);
		textures[TEXTURE::ID::LUIGI_RUN]->LoadFromFile("Images/luigi_run.png");
		frameCount[TEXTURE::ID::LUIGI_RUN] = 3;


		textures[TEXTURE::ID::LUIGI_JUMP] = new Texture2D(renderer);
		textures[TEXTURE::ID::LUIGI_JUMP]->LoadFromFile("Images/luigi_jump.png");
		frameCount[TEXTURE::ID::LUIGI_JUMP] = 1;

		textures[TEXTURE::ID::LUIGI_DIE] = new Texture2D(renderer);
		textures[TEXTURE::ID::LUIGI_DIE]->LoadFromFile("Images/luigi_die.png");
		frameCount[TEXTURE::ID::LUIGI_DIE] = 1;

		textures[TEXTURE::ID::KOOPA] = new Texture2D(renderer);
		textures[TEXTURE::ID::KOOPA]->LoadFromFile("Images/Koopa.png");
		frameCount[TEXTURE::ID::KOOPA] = 3;

		textures[TEXTURE::ID::KOOPA_STUN] = new Texture2D(renderer);
		textures[TEXTURE::ID::KOOPA_STUN]->LoadFromFile("Images/koopa_stun.png");
		frameCount[TEXTURE::ID::KOOPA_STUN] = 2;

		textures[TEXTURE::ID::CRAB] = new Texture2D(renderer);
		textures[TEXTURE::ID::CRAB]->LoadFromFile("Images/crab.png");
		frameCount[TEXTURE::ID::CRAB] = 3;

		textures[TEXTURE::ID::CRAB_STUN] = new Texture2D(renderer);
		textures[TEXTURE::ID::CRAB_STUN]->LoadFromFile("Images/crab_stun.png");
		frameCount[TEXTURE::ID::CRAB_STUN] = 3;

		initialized = true;
	}
}

TextureManager::~TextureManager()
{
	textures[TEXTURE::ID::POW_BLOCK]->Free();
	textures[TEXTURE::ID::FIREBALL]->Free();
	textures[TEXTURE::ID::MARIO_IDLE]->Free();
	textures[TEXTURE::ID::MARIO_RUN]->Free();
	textures[TEXTURE::ID::MARIO_JUMP]->Free();
	textures[TEXTURE::ID::MARIO_DIE]->Free();
	textures[TEXTURE::ID::LUIGI_IDLE]->Free();
	textures[TEXTURE::ID::LUIGI_RUN]->Free();
	textures[TEXTURE::ID::LUIGI_JUMP]->Free();
	textures[TEXTURE::ID::LUIGI_DIE]->Free();
	textures[TEXTURE::ID::KOOPA]->Free();
	textures[TEXTURE::ID::KOOPA_STUN]->Free();
	textures[TEXTURE::ID::CRAB]->Free();
	textures[TEXTURE::ID::CRAB_STUN]->Free();

	delete textures[TEXTURE::ID::POW_BLOCK];
	delete textures[TEXTURE::ID::FIREBALL];
	delete textures[TEXTURE::ID::MARIO_IDLE];
	delete textures[TEXTURE::ID::MARIO_RUN];
	delete textures[TEXTURE::ID::MARIO_JUMP];
	delete textures[TEXTURE::ID::MARIO_DIE];
	delete textures[TEXTURE::ID::LUIGI_IDLE];
	delete textures[TEXTURE::ID::LUIGI_RUN];
	delete textures[TEXTURE::ID::LUIGI_JUMP];
	delete textures[TEXTURE::ID::LUIGI_DIE];
	delete textures[TEXTURE::ID::KOOPA];
	delete textures[TEXTURE::ID::KOOPA_STUN];
	delete textures[TEXTURE::ID::CRAB];
	delete textures[TEXTURE::ID::CRAB_STUN];

}

int TextureManager::GetFrameCount(TEXTURE::ID texture) {
	if (texture != TEXTURE::ID::NONE && texture != TEXTURE::ID::count)
	{
		return frameCount[texture];
	}
	else return 0;
}

TextureManager* TextureManager::Instance() {
	if (!m_instance) {
		m_instance = new TextureManager();
	}

	return m_instance;
}

void TextureManager::Shutdown() {
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}