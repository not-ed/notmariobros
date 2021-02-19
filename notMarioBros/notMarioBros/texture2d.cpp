#include "texture2d.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer) {
	m_renderer = renderer;
}

Texture2D::~Texture2D() {
	Free();

	m_renderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path) {
	// Remove memory used for previous texture
	Free();

	// Load image
	SDL_Surface* p_surface = IMG_Load(path.c_str());
	if (p_surface != nullptr)
	{
		// Color key image to be transparent
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0xFF, 0xFF));
		// Create texture from the pixels found on the surface
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
		if (m_texture == nullptr) {
			cerr << "[!] Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		else {
			m_width = p_surface->w;
			m_height = p_surface->h;
		}

		// The loaded surface is no longer needed
		SDL_FreeSurface(p_surface);
	}
	else {
		cerr << "[!] Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}

	return m_texture != nullptr;
}

void Texture2D::Free() {
	// Check texture actually exists first.
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;

		m_width = 0;
		m_height = 0;
	}
}

// Initializing angle to 0.0 here again will causes issues, so it is not needed.
void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle) {
	SDL_Rect renderLocation = { new_position.x,new_position.y,m_width,m_height };
	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, 0, nullptr, flip);
}