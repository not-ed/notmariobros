#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "texture2d.h"
#include "commons.h"

#include <iostream>
using namespace std;

SDL_Window* g_window = nullptr;

SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;
void Render();

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
			Render();
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

		// Create renderer
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		
		if (g_renderer != nullptr) {
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

		// Load test texture
		g_texture = new Texture2D(g_renderer);
		if (!g_texture->LoadFromFile("Images/test.bmp")) {
			return false;
		}

	}
	
	return true;
}

void CloseSDL() {
	// Release Renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	// Release window and free memory
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	delete g_texture;
	g_texture = nullptr;

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
		if (e.key.keysym.sym == SDLK_q) {
			return true;
		}
		break;
	}

	return false;
}

void Render() {
	// Clear screen
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0);
	SDL_RenderClear(g_renderer);

	g_texture->Render(Vector2D(), SDL_FLIP_NONE);

	// Update Screen
	SDL_RenderPresent(g_renderer);
}