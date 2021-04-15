#pragma once
#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "texturemanager.h"

// Class for automatically managing the sequence of frames that make up a sprite/texture; reducing code repitition in multiple objects that require animation and only exposing what is necessary to the class using it.
class Animator
{
public:
	Animator(TEXTURE::ID tex, float animation_speed);

	void Update(float delta_time);

	// Render the frame in the animation that should currently be displayed.
	void Render(Vector2D new_position, double angle = 0.0);

	// Switch the animation to a given texture ID.
	void SwitchTexture(TEXTURE::ID tex);

	void SetAnimationSpeed(float speed) { animationSpeed = speed; }

	// Set the frame of the current animation to the given number.
	void SetFrame(int frame) { currentFrame = frame; }

	// Set whether the animation should be flipped or not.
	void SetFlip(SDL_RendererFlip state) { flipState = state; }

	TEXTURE::ID GetTextureID() { return currentTexture; }

	// Get how many frames are in the current animation.
	int GetFrameCount() { return TextureManager::Instance()->GetFrameCount(currentTexture); }

	int GetFrameWidth() { return TextureManager::Instance()->GetTexture(currentTexture)->GetWidth() / GetFrameCount(); }
	int GetFrameHeight() { return TextureManager::Instance()->GetTexture(currentTexture)->GetHeight(); }
private:

	TEXTURE::ID currentTexture = TEXTURE::ID::NONE;

	// How long the current frame has been displayed
	float currentFrameTime = 0.0f;
	int currentFrame = 0;
	float animationSpeed = 0.0f;
	
	// How the displayed texture is flipped.
	SDL_RendererFlip flipState = SDL_FLIP_NONE;

	SDL_Rect renderPortion = SDL_Rect{0,0,1,1};
};

#endif