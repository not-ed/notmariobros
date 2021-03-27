#pragma once
#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "texturemanager.h"

// Class for management of animation
class Animator
{
public:
	Animator(TEXTURE::ID tex, float animation_speed);
	void Update(float deltaTime);
	void Render(Vector2D new_position, double angle = 0.0);
	void SwitchTexture(TEXTURE::ID tex);
	void SetAnimationSpeed(float speed) { animationSpeed = speed; }
	void SetFrame(int frame) { currentFrame = frame; }
	void SetFlip(SDL_RendererFlip state) { flipState = state; }
private:
	TEXTURE::ID currentSprite = TEXTURE::ID::NONE;
	float animationSpeed;
	float currentFrameTime = 0.0f;
	int currentFrame = 0;
	SDL_RendererFlip flipState = SDL_FLIP_NONE;
	SDL_Rect renderPortion = SDL_Rect{0,0,1,1};
};

#endif