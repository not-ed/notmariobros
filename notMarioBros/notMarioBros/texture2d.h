#pragma once
#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <SDL.h>
#include <string>
#include "commons.h"

// Class for loading and holding a texture.
class Texture2D {
public:
	Texture2D(SDL_Renderer* game_renderer);
	~Texture2D();

	bool LoadFromFile(std::string path);

	//Destroy the texture and free it from memory
	void Free();

	void Render(Vector2D new_position, SDL_RendererFlip flip, double angle = 0.0);
	void Render(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angle = 0.0);

	int GetWidth() {if (texture != nullptr) { return width; }else { return 1; }}
	int GetHeight() { if (texture != nullptr) { return height; } else { return 1; } }

	
private:
	SDL_Renderer* renderer;
	SDL_Texture* texture;

	int width;
	int height;
};

#endif