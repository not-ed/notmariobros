#pragma once
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL_mixer.h>

namespace SOUND {
	enum ID {
		PLAYER_JUMP,
		PLAYER_DIE,
		POW_BLOCK,
		ENEMY_HURT,
		ENEMY_DIE,
		COIN,
		count
	};
}

namespace MUSIC {
	enum ID {
		MARIO,
		UNDERWORLD,
		count
	};
}

// Singleton class for keeping all sound and music assets in one place that can be referenced by the rest of the program
class SoundManager
{
public:
	~SoundManager();

	// Return a pointer to the singleton object so that requests for a collision check can be made.
	static SoundManager* Instance();

	// Startup/shutdown
	void LoadAssets();
	void Shutdown();

	// Play a sound effect once
	void PlaySound(SOUND::ID id);

	// Play a music track on loop
	void PlayMusic(MUSIC::ID id);
	void StopMusic();

private:

	static SoundManager* instance;

	Mix_Chunk* sounds[SOUND::ID::count];
	Mix_Music* music[MUSIC::ID::count];

	// If the singleton object has already been initialized.
	bool initialized = false;
};

#endif