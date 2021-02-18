#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"

#include <iostream>
using namespace std;

SDL_Window* g_window = nullptr;

bool InitSDL();
void CloseSDL();
bool Update();

int main(int argc, char* args[]) {

	if (InitSDL())
	{
		// Whether user wishes to quit / game session is running
		bool quit = false;

		// Entering game loop
		while (!quit) {
			quit = Update();
		}
	}

	CloseSDL();

	return 0;
}

bool InitSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cerr << "[!] SDL failed to initialize. Error: " << SDL_GetError() << endl;
		return false;
	}
	else {
		g_window = SDL_CreateWindow(
			"Not Mario Bros.",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		// Window failed to be created from above
		if (g_window == nullptr) {
			cerr << "[!] SDL window was not created. Error: " << SDL_GetError() << endl;
			return false;
		}
	}
	
	return true;
}

void CloseSDL() {
	// Release window and free memory
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	// Quit additional SDL systems
	IMG_Quit();
	SDL_Quit();
}

bool Update() {
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
		if (e.key.keysym.scancode == SDL_SCANCODE_Q) {
			return true;
		}
		break;
	}

	return false;
}