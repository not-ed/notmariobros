#include "gamescreentitle.h"
#include "texture2d.h"
#include "soundmanager.h"

#include "charactermario.h"
// The required parameters also need to be passed through the GameScreens constructor.
GameScreenTitle::GameScreenTitle(SDL_Renderer* game_renderer, ScoreCounter* score_counter) : GameScreen(game_renderer,score_counter) {
	SetUpLevel();
	scoreCounter->Reset();
}

bool GameScreenTitle::SetUpLevel() {
	// Stop any music if it is already playing, and start playing the relevant music after.
	SoundManager::Instance()->StopMusic();
	SoundManager::Instance()->PlayMusic(MUSIC::ID::UNDERWORLD);

	// Pull latest high score from file and set the initial display time of the first menu phase to its intended time
	scoreData = HighScore::GetLatestHighscore();
	scoreTableTimer.SetTime(7.5f, true);

	return true;
}

void GameScreenTitle::Render() {
	// Render game logo
	logo.Render(Vector2D(56, 32), 0.0);
	Text::Draw("(not)", IntVector2D(96, 32), FONT::ID::MARIO, FONT::ALLIGNMENT::LEFT);

	if (displayingScores) // Draw the high score table.
	{
		
		Text::Draw("TOP PLUMBERS", IntVector2D(160, 192), FONT::ID::GOLD, FONT::ALLIGNMENT::LEFT);

		for (int i = 0; i < displayedScores; i++)
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

			// Draw name and score associated to position i
			Text::Draw(scoreData.GetName(i), IntVector2D(144, 224 + (16 * i)), i_font, FONT::ALLIGNMENT::LEFT);
			Text::Draw(std::to_string(scoreData.GetScore(i)), IntVector2D(367, 224 + (16 * i)), i_font, FONT::ALLIGNMENT::RIGHT);
		}
	}
	else { // Game start prompts
		Text::Draw("1 Player Game [1]", IntVector2D(120, 240), FONT::ID::MARIO, FONT::ALLIGNMENT::LEFT);
		Text::Draw("2 Player Game [2]", IntVector2D(120, 304), FONT::ID::LUIGI, FONT::ALLIGNMENT::LEFT);
	}
}

void GameScreenTitle::Update(float delta_time, SDL_Event e) {
	logo.Update(delta_time);
	scoreTableTimer.Update(delta_time);

	if (scoreTableTimer.IsExpired())
	{
		if (displayingScores)
		{
			// Still some scores left to display
			if (displayedScores < SCORE_TABLE_SIZE)
			{
				displayedScores++;

				scoreTableTimer.Reset();

				if (displayedScores == SCORE_TABLE_SIZE)
				{
					scoreTableTimer.SetTime(6.0f, true);
				}
			}
			else { // The last score was displayed on the last timer - switch back to the Game Start prompt phase
				displayedScores = 0;

				displayingScores = false;

				scoreTableTimer.SetTime(7.5f, true);
			}
		}
		else { // Switch from Game Start prompt phase to high score table.
			displayingScores = true;

			scoreTableTimer.SetTime(.75f, true);
		}
	}
}
