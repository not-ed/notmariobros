#include "texturemanager.h"

TextureManager* TextureManager::instance = nullptr;

void TextureManager::LoadAssets(SDL_Renderer* renderer) {
	if (!initialized) {
		textures[TEXTURE::ID::NONE] = new Texture2D(renderer);

		textures[TEXTURE::ID::LOGO] = new Texture2D(renderer);
		textures[TEXTURE::ID::LOGO]->LoadFromFile("Images/logo.png");
		frameCount[TEXTURE::ID::LOGO] = 3;

		textures[TEXTURE::ID::POW_BLOCK] = new Texture2D(renderer);
		textures[TEXTURE::ID::POW_BLOCK]->LoadFromFile("Images/PowBlock.png");
		frameCount[TEXTURE::ID::POW_BLOCK] = 3;

		textures[TEXTURE::ID::COIN] = new Texture2D(renderer);
		textures[TEXTURE::ID::COIN]->LoadFromFile("Images/Coin.png");
		frameCount[TEXTURE::ID::COIN] = 5;

		textures[TEXTURE::ID::FIREBALL] = new Texture2D(renderer);
		textures[TEXTURE::ID::FIREBALL]->LoadFromFile("Images/fireball.png");
		frameCount[TEXTURE::ID::FIREBALL] = 4;

		textures[TEXTURE::ID::FIREBALL_RED] = new Texture2D(renderer);
		textures[TEXTURE::ID::FIREBALL_RED]->LoadFromFile("Images/fireball_angry.png");
		frameCount[TEXTURE::ID::FIREBALL_RED] = 4;

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
		frameCount[TEXTURE::ID::MARIO_DIE] = 2;

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
		frameCount[TEXTURE::ID::LUIGI_DIE] = 2;

		textures[TEXTURE::ID::KOOPA] = new Texture2D(renderer);
		textures[TEXTURE::ID::KOOPA]->LoadFromFile("Images/Koopa.png");
		frameCount[TEXTURE::ID::KOOPA] = 3;

		textures[TEXTURE::ID::KOOPA_STUN] = new Texture2D(renderer);
		textures[TEXTURE::ID::KOOPA_STUN]->LoadFromFile("Images/koopa_stun.png");
		frameCount[TEXTURE::ID::KOOPA_STUN] = 2;

		textures[TEXTURE::ID::KOOPA_DIE] = new Texture2D(renderer);
		textures[TEXTURE::ID::KOOPA_DIE]->LoadFromFile("Images/koopa_die.png");
		frameCount[TEXTURE::ID::KOOPA_DIE] = 4;

		textures[TEXTURE::ID::KOOPA_ANGRY] = new Texture2D(renderer);
		textures[TEXTURE::ID::KOOPA_ANGRY]->LoadFromFile("Images/koopa_angry.png");
		frameCount[TEXTURE::ID::KOOPA_ANGRY] = 3;

		textures[TEXTURE::ID::KOOPA_ANGRY_STUN] = new Texture2D(renderer);
		textures[TEXTURE::ID::KOOPA_ANGRY_STUN]->LoadFromFile("Images/koopa_angry_stun.png");
		frameCount[TEXTURE::ID::KOOPA_ANGRY_STUN] = 2;

		textures[TEXTURE::ID::KOOPA_ANGRY_DIE] = new Texture2D(renderer);
		textures[TEXTURE::ID::KOOPA_ANGRY_DIE]->LoadFromFile("Images/koopa_angry_die.png");
		frameCount[TEXTURE::ID::KOOPA_ANGRY_DIE] = 4;

		textures[TEXTURE::ID::CRAB] = new Texture2D(renderer);
		textures[TEXTURE::ID::CRAB]->LoadFromFile("Images/crab.png");
		frameCount[TEXTURE::ID::CRAB] = 3;

		textures[TEXTURE::ID::CRAB_STUN] = new Texture2D(renderer);
		textures[TEXTURE::ID::CRAB_STUN]->LoadFromFile("Images/crab_stun.png");
		frameCount[TEXTURE::ID::CRAB_STUN] = 2;

		textures[TEXTURE::ID::CRAB_DIE] = new Texture2D(renderer);
		textures[TEXTURE::ID::CRAB_DIE]->LoadFromFile("Images/crab_die.png");
		frameCount[TEXTURE::ID::CRAB_DIE] = 4;

		textures[TEXTURE::ID::CRAB_ANGRY] = new Texture2D(renderer);
		textures[TEXTURE::ID::CRAB_ANGRY]->LoadFromFile("Images/crab_angry.png");
		frameCount[TEXTURE::ID::CRAB_ANGRY] = 3;

		textures[TEXTURE::ID::CRAB_ANGRY_STUN] = new Texture2D(renderer);
		textures[TEXTURE::ID::CRAB_ANGRY_STUN]->LoadFromFile("Images/crab_angry_stun.png");
		frameCount[TEXTURE::ID::CRAB_ANGRY_STUN] = 2;

		textures[TEXTURE::ID::CRAB_ANGRY_DIE] = new Texture2D(renderer);
		textures[TEXTURE::ID::CRAB_ANGRY_DIE]->LoadFromFile("Images/crab_angry_die.png");
		frameCount[TEXTURE::ID::CRAB_ANGRY_DIE] = 4;

		textures[TEXTURE::ID::ICICLE] = new Texture2D(renderer);
		textures[TEXTURE::ID::ICICLE]->LoadFromFile("Images/icicle.png");
		frameCount[TEXTURE::ID::ICICLE] = 3;

		initialized = true;
	}
}

TextureManager::~TextureManager()
{
	textures[TEXTURE::ID::NONE]->Free();
	textures[TEXTURE::ID::LOGO]->Free();
	textures[TEXTURE::ID::POW_BLOCK]->Free();
	textures[TEXTURE::ID::COIN]->Free();
	textures[TEXTURE::ID::FIREBALL]->Free();
	textures[TEXTURE::ID::FIREBALL_RED]->Free();
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
	textures[TEXTURE::ID::KOOPA_DIE]->Free();
	textures[TEXTURE::ID::KOOPA_ANGRY]->Free();
	textures[TEXTURE::ID::KOOPA_ANGRY_STUN]->Free();
	textures[TEXTURE::ID::KOOPA_ANGRY_DIE]->Free();
	textures[TEXTURE::ID::CRAB]->Free();
	textures[TEXTURE::ID::CRAB_STUN]->Free();
	textures[TEXTURE::ID::CRAB_DIE]->Free();
	textures[TEXTURE::ID::CRAB_ANGRY]->Free();
	textures[TEXTURE::ID::CRAB_ANGRY_STUN]->Free();
	textures[TEXTURE::ID::CRAB_ANGRY_DIE]->Free();
	textures[TEXTURE::ID::ICICLE]->Free();

	delete textures[TEXTURE::ID::NONE];
	delete textures[TEXTURE::ID::LOGO];
	delete textures[TEXTURE::ID::POW_BLOCK];
	delete textures[TEXTURE::ID::COIN];
	delete textures[TEXTURE::ID::FIREBALL];
	delete textures[TEXTURE::ID::FIREBALL_RED];
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
	delete textures[TEXTURE::ID::KOOPA_DIE];
	delete textures[TEXTURE::ID::KOOPA_ANGRY];
	delete textures[TEXTURE::ID::KOOPA_ANGRY_STUN];
	delete textures[TEXTURE::ID::KOOPA_ANGRY_DIE];
	delete textures[TEXTURE::ID::CRAB];
	delete textures[TEXTURE::ID::CRAB_STUN];
	delete textures[TEXTURE::ID::CRAB_DIE];
	delete textures[TEXTURE::ID::CRAB_ANGRY];
	delete textures[TEXTURE::ID::CRAB_ANGRY_STUN];
	delete textures[TEXTURE::ID::CRAB_ANGRY_DIE];
	delete textures[TEXTURE::ID::ICICLE];

}

int TextureManager::GetFrameCount(TEXTURE::ID texture) {
	if (texture != TEXTURE::ID::NONE && texture != TEXTURE::ID::count)
	{
		return frameCount[texture];
	}
	else return 1;
}

TextureManager* TextureManager::Instance() {
	if (!instance) {
		instance = new TextureManager();
	}

	return instance;
}

void TextureManager::Shutdown() {
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}