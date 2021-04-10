#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "commons.h"
#include "gamescreenmanager.h"
#include <SDL_mixer.h>
#include "soundmanager.h"
#include "texturemanager.h"
#include "textrenderer.h"
#include <iostream>

using namespace std;

SDL_Window* gameWindow = nullptr;

SDL_Renderer* gameRenderer = nullptr;

GameScreenManager* gameScreenManager;

// Number of ticks that passed when the last frame was handled, which can be used with the current tick amount to calculate delta time.
Uint32 previousFrameTime;

bool Update();
void Render();

bool InitSDL();
void CloseSDL();

int main(int argc, char* args[]) {

	if (InitSDL())
	{
		// Set up new Game Screen Manager and initialize its current screen to the main menu
		gameScreenManager = new GameScreenManager(gameRenderer, SCREEN_MENU);

		previousFrameTime = SDL_GetTicks();

		// Whether user wishes to quit / game session is running
		bool quit = false;

		// Entering game loop
		while (!quit) {
			Render();
			quit = Update();
		}
	}

	// Perform shutdown cleanup
	CloseSDL();

	return 0;
}

bool InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "[!] SDL failed to initialize. Error: " << SDL_GetError() << endl;
		return false;
	}
	else {
		gameWindow = SDL_CreateWindow(
			"Not Mario Bros.",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		// Window failed to be created from above
		if (gameWindow == nullptr) {
			cerr << "[!] SDL window was not created. Error: " << SDL_GetError() << endl;
			return false;
		}

		// Create renderer
		gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
		
		if (gameRenderer != nullptr) {
			int imageFlags = IMG_INIT_PNG;

			if (!(IMG_Init(imageFlags) & imageFlags)) {
				cerr << "[!] SDL_Image could not be initialized. Error: " << IMG_GetError() << endl;
				return false;
			}
		}
		else { // Failed to create renderer
			cerr << "[!] Renderer could not be initialized. Error: " << SDL_GetError() << endl;
			return false;
		}

		// Initialise sound
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			cerr << "[!] Mixer could not be initialized. Error: " << Mix_GetError() << endl;
			return false;
		}
	}

	// Load texture, sound and font assets.
	TextureManager::Instance()->LoadAssets(gameRenderer);
	SoundManager::Instance()->LoadAssets();
	Text::Initialize(gameRenderer);
	
	return true;
}

void CloseSDL() {
	// Destroy Game Screen Manager
	delete gameScreenManager;
	gameScreenManager = nullptr;

	// Release Renderer
	SDL_DestroyRenderer(gameRenderer);
	gameRenderer = nullptr;

	// Release window and free memory
	SDL_DestroyWindow(gameWindow);
	gameWindow = nullptr;

	// Shutdown sound manager
	SoundManager::Instance()->Shutdown();

	// Shutdown texture manager
	TextureManager::Instance()->Shutdown();

	// Shutdown the text renderer
	Text::Shutdown();

	// Quit additional SDL systems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

bool Update() {
	Uint32 new_time = SDL_GetTicks();

	SDL_Event e;

	// Get events this update cycle
	SDL_PollEvent(&e);

	// Handle/dispatch events
	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_q) {
			return true;
		}
		if (e.key.keysym.sym == SDLK_1) {
			gameScreenManager->ChangeScreen(SCREENS::SCREEN_MENU);
		}
		if (e.key.keysym.sym == SDLK_2) { 
			gameScreenManager->ChangeScreen(SCREENS::SCREEN_LEVEL1);
		}
		break;
		// TODO: Implement button presses to start game from main menu.
	}

	// Dividing the amount of time between the first and last frame in ticks by 1000.0 gives us the deltaTime in milliseconds.
	gameScreenManager->Update((float)(new_time - previousFrameTime) / 1000.0f,e);

	previousFrameTime = new_time;

	return false;
}

void Render() {
	// Clear screen
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
	SDL_RenderClear(gameRenderer);

	gameScreenManager->Render();

	// Update Screen
	SDL_RenderPresent(gameRenderer);
}