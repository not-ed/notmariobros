#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"

#include <iostream>
using namespace std;

SDL_Window* g_window = nullptr;

SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;
void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();

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
		g_texture = LoadTextureFromFile("Images/test.bmp");
		if (g_texture == nullptr) {
			return false;
		}

	}
	
	return true;
}

void CloseSDL() {
	//Clear Texture
	FreeTexture();
	// Release Renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

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

	SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	// Render to screen
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

	// Update Screen
	SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(string path) {
	// Remove memory used for previous texture
	FreeTexture();

	SDL_Texture* p_texture = nullptr;

	// Load image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		// Create texture from the pixels found on the surface
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
		if (p_texture == nullptr) {
			cerr << "[!] Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}

		// The loaded surface is no longer needed
		SDL_FreeSurface(p_surface);
	}
	else {
		cerr << "[!] Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}

	return p_texture;
}

void FreeTexture() {
	// Check texture actually exists first.
	if (g_texture != nullptr) {
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}