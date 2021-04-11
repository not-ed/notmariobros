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
		COIN,
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
		KOOPA_DIE,
		KOOPA_ANGRY,
		KOOPA_ANGRY_STUN,
		KOOPA_ANGRY_DIE,
		CRAB,
		CRAB_STUN,
		ICICLE,
		count
	};
}

// Singleton class for keeping a single copy of each sprite/texture in one place that can be accessed by the whole program if needed.
class TextureManager
{
public:
	~TextureManager();

	// Return a pointer to the singleton object so that requests for a collision check can be made.
	static TextureManager* Instance();
	
	int GetFrameCount(TEXTURE::ID texture);
	Texture2D* GetTexture(TEXTURE::ID texture) { return textures[texture]; }

	//Startup/Shutdown
	void LoadAssets(SDL_Renderer* renderer);
	void Shutdown();
private:

	static TextureManager* instance;

	Texture2D* textures[TEXTURE::ID::count];
	// How many frames are in a given Texture
	int frameCount[TEXTURE::ID::count];

	// If the singleton object has already been initialized.
	bool initialized = false;
};

#endif