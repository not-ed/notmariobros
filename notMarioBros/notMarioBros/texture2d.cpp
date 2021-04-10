#include "texture2d.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* game_renderer) {
	renderer = game_renderer;
}

Texture2D::~Texture2D() {
	Free();

	renderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path) {
	// Remove memory used for previous texture
	Free();

	// Load image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		// Color key image to be transparent - Pixels that are cyan (R:0,G:255,B:255) will be treated as transparent
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0xFF, 0xFF));

		// Create texture from the pixels found on the surface
		texture = SDL_CreateTextureFromSurface(renderer, p_surface);
		if (texture == nullptr) {
			cerr << "[!] Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		else {
			width = p_surface->w;
			height = p_surface->h;
		}

		// The loaded surface is no longer needed
		SDL_FreeSurface(p_surface);
	}
	else {
		cerr << "[!] Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}

	return texture != nullptr;
}

void Texture2D::Free() {
	// Check texture actually exists first.
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;

		width = 0;
		height = 0;
	}
}

// Initializing angle to 0.0 here again will causes issues, so it is not needed.
void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle) {

	SDL_Rect renderLocation = { new_position.x,new_position.y,width,height };

	SDL_RenderCopyEx(renderer, texture, nullptr, &renderLocation, 0, nullptr, flip);
}

void Texture2D::Render(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angle) {

	SDL_RenderCopyEx(renderer, texture, &src_rect, &src_dest, angle, nullptr, flip);
}