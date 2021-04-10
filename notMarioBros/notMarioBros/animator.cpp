#include "animator.h"

Animator::Animator(TEXTURE::ID tex, float animation_speed) {
	SwitchTexture(tex);
	SetAnimationSpeed(animation_speed);
}

void Animator::Update(float delta_time) {
	currentFrameTime += delta_time;

	// Go to next frame (or loop to start) if enough frame time has passed.
	if (currentFrameTime >= animationSpeed)
	{
		currentFrameTime = 0;
		currentFrame++;
		if (currentFrame > TextureManager::Instance()->GetFrameCount(currentTexture) - 1)
		{
			currentFrame = 0;
		}
	}
}

void Animator::SwitchTexture(TEXTURE::ID tex) {
	if (tex != currentTexture) {
		renderPortion.w = TextureManager::Instance()->GetTexture(tex)->GetWidth() / TextureManager::Instance()->GetFrameCount(tex);
		renderPortion.h = TextureManager::Instance()->GetTexture(tex)->GetHeight();

		currentTexture = tex;

		SetFrame(0);
	}
}

void Animator::Render(Vector2D new_position, double angle) {
	// Create a rect for where the current frame will be drawn.
	SDL_Rect destination_rect;
	destination_rect.x = new_position.x;
	destination_rect.y = new_position.y;
	destination_rect.w = renderPortion.w;
	destination_rect.h = renderPortion.h;

	// Get the relevant frame position to draw.
	renderPortion.x = currentFrame * renderPortion.w;

	TextureManager::Instance()->GetTexture(currentTexture)->Render(renderPortion, destination_rect, flipState, angle);
}