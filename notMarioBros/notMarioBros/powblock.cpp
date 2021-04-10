#include "powblock.h"
#include <iostream>

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* level)
{
	levelMap = level;
	hitsLeft = 3;
	position = Vector2D((SCREEN_WIDTH * 0.5f)-anim.GetFrameWidth() * 0.5f, 260);
}

PowBlock::~PowBlock()
{
	// Renderer does not need to be deleted, it is shared with other areas of the program
	renderer = nullptr;

	levelMap = nullptr;
}

void PowBlock::Render() {
	if (hitsLeft > 0)
	{
		anim.SetFrame(-1+(hitsLeft));
		anim.Render(position,0.0);
	}
}

void PowBlock::TakeHit() {
	hitsLeft--;

	SoundManager::Instance()->PlaySound(SOUND::ID::POW_BLOCK);

	if (hitsLeft <= 0) {
		hitsLeft = 0;

		// Change relevant tiles in level to be empty space
		levelMap->ChangeTileAt(8, 7, 0);
		levelMap->ChangeTileAt(8, 8, 0);
	}
}