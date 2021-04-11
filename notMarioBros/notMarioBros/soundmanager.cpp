#include "soundmanager.h"
#include <iostream>

//Initialize instance to nullptr
SoundManager* SoundManager::instance = nullptr;

void SoundManager::LoadAssets() {
	if (!initialized) {
		//Sounds
		sounds[SOUND::ID::PLAYER_JUMP] = Mix_LoadWAV("Music/jump.wav");
		sounds[SOUND::ID::PLAYER_DIE] = Mix_LoadWAV("Music/die.wav");
		sounds[SOUND::ID::POW_BLOCK] = Mix_LoadWAV("Music/pow.wav");
		sounds[SOUND::ID::ENEMY_HURT] = Mix_LoadWAV("Music/enemy_hurt.wav");
		sounds[SOUND::ID::ENEMY_DIE] = Mix_LoadWAV("Music/enemy_die.wav");
		sounds[SOUND::ID::COIN] = Mix_LoadWAV("Music/coin_pickup.wav");

		//Music
		music[MUSIC::ID::MARIO] = Mix_LoadMUS("Music/Mario.mp3");
		music[MUSIC::ID::UNDERWORLD] = Mix_LoadMUS("Music/MarioUnderworld.mp3");
		
		initialized = true;
	}
}

SoundManager::~SoundManager()
{
	//Sounds
	Mix_FreeChunk(sounds[SOUND::ID::PLAYER_JUMP]);
	sounds[SOUND::ID::PLAYER_JUMP] = nullptr;
	Mix_FreeChunk(sounds[SOUND::ID::PLAYER_DIE]);
	sounds[SOUND::ID::PLAYER_DIE] = nullptr;
	Mix_FreeChunk(sounds[SOUND::ID::POW_BLOCK]);
	sounds[SOUND::ID::POW_BLOCK] = nullptr;
	Mix_FreeChunk(sounds[SOUND::ID::ENEMY_HURT]);
	sounds[SOUND::ID::ENEMY_HURT] = nullptr;
	Mix_FreeChunk(sounds[SOUND::ID::ENEMY_DIE]);
	sounds[SOUND::ID::ENEMY_DIE] = nullptr;
	Mix_FreeChunk(sounds[SOUND::ID::COIN]);
	sounds[SOUND::ID::COIN] = nullptr;

	//Music
	Mix_FreeMusic(music[MUSIC::ID::MARIO]);
	music[MUSIC::ID::MARIO] = nullptr;
	Mix_FreeMusic(music[MUSIC::ID::UNDERWORLD]);
	music[MUSIC::ID::UNDERWORLD] = nullptr;

	instance = nullptr;
}

SoundManager* SoundManager::Instance() {
	if (!instance) {
		instance = new SoundManager();
	}

	return instance;
}

void SoundManager::PlaySound(SOUND::ID id) {
	if (id != SOUND::ID::count) {
		if (sounds[id] != nullptr) { Mix_PlayChannel(-1, sounds[id], 0); }
	}
}

void SoundManager::PlayMusic(MUSIC::ID id) {
	if (id != MUSIC::ID::count) {
		if (music[id] != nullptr) { Mix_PlayMusic(music[id], -1); }
	}
}

void SoundManager::StopMusic() {
	Mix_HaltMusic();
}

void SoundManager::Shutdown() {
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}