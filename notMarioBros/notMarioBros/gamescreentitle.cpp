#include "gamescreentitle.h"
#include <iostream>
#include "texture2d.h"
#include "soundmanager.h"

// The required parameters also need to be passed through the GameScreens constructor.
GameScreenTitle::GameScreenTitle(SDL_Renderer* renderer) : GameScreen(renderer) {
	SetUpLevel();
}


GameScreenTitle::~GameScreenTitle()
{

}

void GameScreenTitle::Render() {
	//56, 32 (logo)
	TextureManager::Instance()->GetTexture(TEXTURE::ID::LOGO)->Render(Vector2D(56, 32), SDL_FLIP_NONE, 0.0);
	//160 192
	Text::Draw("TOP PLUMBERS", IntVector2D(160, 192), FONT::ID::MARIO, FONT::ALLIGNMENT::LEFT);
	//144,224
	for (int i = 0; i < SCORE_TABLE_SIZE; i++)
	{
		FONT::ID i_font;
		if (i == 0)
		{
			i_font = FONT::ID::GOLD;  // Gold Text (1st Place)
		}
		else if (i <= 4) {
			i_font = FONT::ID::SILVER;// Silver Text (2nd-5th Place)
		}
		else {
			i_font = FONT::ID::REGULAR; // Normal Text (6th-10th Place)
		}
		Text::Draw(scoreData.GetName(i), IntVector2D(144, 224 + (16 * i)), i_font, FONT::ALLIGNMENT::LEFT);
		Text::Draw(std::to_string(scoreData.GetScore(i)), IntVector2D(367, 224 + (16 * i)), i_font, FONT::ALLIGNMENT::RIGHT);
	}
}

void GameScreenTitle::Update(float deltaTime, SDL_Event e) {

}

bool GameScreenTitle::SetUpLevel() {
	SoundManager::Instance()->StopMusic();
	SoundManager::Instance()->PlayMusic(MUSIC::ID::UNDERWORLD);

	scoreData = HighScore::GetLatestHighscore();

	return true;
}