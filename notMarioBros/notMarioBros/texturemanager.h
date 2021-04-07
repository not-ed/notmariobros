#pragma once
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "SDL.h"
#include "texture2d.h"

namespace TEXTURE {
	enum ID {
		NONE,
		LOGO,
		POW_BLOCK,
		FIREBALL,
		MARIO_IDLE,
		MARIO_RUN,
		MARIO_JUMP,
		MARIO_DIE,
		LUIGI_IDLE,
		LUIGI_RUN,
		LUIGI_JUMP,
		LUIGI_DIE,
		KOOPA,
		KOOPA_STUN,
		CRAB,
		CRAB_STUN,
		count
	};
}

class TextureManager
{
public:
	~TextureManager();
	static TextureManager* Instance();
	void LoadAssets(SDL_Renderer* renderer);
	int GetFrameCount(TEXTURE::ID texture);
	Texture2D* GetTexture(TEXTURE::ID texture) { return textures[texture]; };
	void Shutdown();
private:
	static TextureManager* m_instance;
	Texture2D* textures[TEXTURE::ID::count];
	int frameCount[TEXTURE::ID::count];
	bool initialized = false;
};

#endif