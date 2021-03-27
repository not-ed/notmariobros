#include "animator.h"

Animator::Animator(TEXTURE::ID tex, float animation_speed) {
	SwitchTexture(tex);
	SetAnimationSpeed(animation_speed);
}

void Animator::Update(float deltaTime) {
	currentFrameTime += deltaTime;
	if (currentFrameTime >= animationSpeed)
	{
		currentFrameTime = 0;
		currentFrame++;
		if (currentFrame > TextureManager::Instance()->GetFrameCount(currentSprite) - 1)
		{
			currentFrame = 0;
		}
	}
}

void Animator::SwitchTexture(TEXTURE::ID tex) {
	if (tex != currentSprite) {
		renderPortion.w = TextureManager::Instance()->GetTexture(tex)->GetWidth() / TextureManager::Instance()->GetFrameCount(tex);
		renderPortion.h = TextureManager::Instance()->GetTexture(tex)->GetHeight();
		currentSprite = tex;
		SetFrame(0);
	}
}

void Animator::Render(Vector2D new_position, double angle) {
	SDL_Rect destination_rect; //= SDL_Rect(new_position.x, new_position.y, renderPortion.w, renderPortion.h);
	destination_rect.x = new_position.x;
	destination_rect.y = new_position.y;
	destination_rect.w = renderPortion.w;
	destination_rect.h = renderPortion.h;
	renderPortion.x = currentFrame * renderPortion.w;
	TextureManager::Instance()->GetTexture(currentSprite)->Render(renderPortion, destination_rect, flipState, angle);
}

//void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle) {
//	SDL_Rect renderLocation = { new_position.x,new_position.y,m_width,m_height };
//	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, 0, nullptr, flip);
//}
//
//void Texture2D::Render(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angle) {
//	SDL_RenderCopyEx(m_renderer, m_texture, &src_rect, &src_dest, angle, nullptr, flip);
//}