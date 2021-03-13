#pragma once
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <SDL_mixer.h>

namespace SOUND {
	enum ID {
		PLAYER_JUMP,
		PLAYER_DIE,
		POW_BLOCK,
		ENEMY_DIE,
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

class SoundManager
{
public:
	~SoundManager();
	static SoundManager* Instance();

	void PlaySound(SOUND::ID id);
	void PlayMusic(MUSIC::ID id);
	void StopMusic();

private:
	SoundManager();
	void LoadAssets();

	static SoundManager* m_instance;
	Mix_Chunk* sounds[SOUND::ID::count];
	Mix_Music* music[MUSIC::ID::count];
};

#endif