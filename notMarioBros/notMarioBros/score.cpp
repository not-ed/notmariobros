#include "score.h"
#include <iostream>

namespace HighScore {

	// Anonymous namespace - Only accessible to things already inside the HighScore namespace
	namespace {

		// Generate (or wipe over the existing one if it exists due to truncation) a fresh High Score data file.
		HighScoreData CreateFreshDataFile() {
			std::ofstream outFile;
			HighScoreData data;

			// Truncation wipes the files contents automatically and automatically generates the file if it does not exist already.
			outFile.open("Data/Score/highscores.nmb", std::ios::trunc);

			std::cout << "Generating new score file..." << std::endl;

			if (outFile.is_open())
			{
				for (int i = 0; i < SCORE_TABLE_SIZE; i++)
				{
					// Write "--- 0 \n"
					outFile << "--- ";
					outFile << 0 << "\n";

					data.name[i] = "---";
					data.score[i] = 0;
				}
			}

			outFile.close();
			return data;
		}

		// Write the contents of a HighScoreData packet to file
		void WriteScoreFileData(HighScoreData score_data) {
			std::ofstream outFile;

			outFile.open(SCORE_FILE_PATH, std::ios::trunc);

			if (outFile.is_open())
			{
				// Write a name and its score to each line
				for (int i = 0; i < SCORE_TABLE_SIZE; i++)
				{
					outFile << score_data.GetName(i) << " ";
					outFile << score_data.GetScore(i) << "\n";
				}
			}

			outFile.close();
		}
	}

	// Pull down the latest high score from file.
	HighScoreData GetLatestHighscore() {
		HighScoreData data;

		std::ifstream scoreFile;
		scoreFile.open(SCORE_FILE_PATH);

		if (scoreFile.is_open())
		{
			// Reach each name and its score in sequence
			for (int i = 0; i < SCORE_TABLE_SIZE; i++)
			{
				scoreFile >> data.name[i];
				scoreFile >> data.score[i];
			}
			scoreFile.close();
		}
		else {
			// If a score file doesn't exist, create a new one and return an empty table accordingly.
			data = CreateFreshDataFile();
		}

		return data;
	}

	// Submit a score to the table, and then write changes to the disk.
	void SubmitScoreEntry(const char name[3], int score) {
		// Pull the latest table values based on what is held on-disk
		HighScoreData latest_data = GetLatestHighscore();

		for (int i = 0; i < SCORE_TABLE_SIZE; i++)
		{
			// A new score has been achieved
			if (score >= latest_data.GetScore(i)) {

				// Push all scores after the new score position downwards.
				for (int j = SCORE_TABLE_SIZE - 1; j > i; j--)
				{
					latest_data.score[j] = latest_data.score[j - 1];
					latest_data.name[j] = latest_data.name[j - 1];
				}

				// Put the submitted name-score combo in its new place.
				latest_data.name[i] = name;
				latest_data.score[i] = score;
				break;
			}
		}

		// Write the changes to the highscore file.
		WriteScoreFileData(latest_data);
	}

	bool NewScoreAchieved(int score) {
		// Pull the latest table values based on what is held on-disk
		HighScoreData latest_data = GetLatestHighscore();
		// Push all scores after the new score position downwards.
		for (int i = 0; i < SCORE_TABLE_SIZE; i++)
		{
			if (score >= latest_data.GetScore(i))
			{
				return true;
			}
		}
		return false;
	}
}





void ScoreNameEntryWindow::Update(float delta_time, SDL_Event e) {
	switch (e.type)
	{
	case SDL_KEYDOWN:
		if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a) {
			SwitchLetter(-1); // Cycle to name character on left
		}
		if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d) {
			SwitchLetter(1); // Cycle to name character on right
		}
		if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w) {
			IncrementLetterCharacter(-1); // Cycle selected character down
		}
		if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s) {
			IncrementLetterCharacter(1); // Cycle selected character up
		}
		if (e.key.keysym.sym == SDLK_z) { // Submit name
			Close();
		}
		break;
	}
}

void ScoreNameEntryWindow::Render() {
	if (renderer != nullptr)
	{
		// Set to black
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_Rect r = { 0, 136, SCREEN_WIDTH, 126 };
		SDL_RenderFillRect(renderer, &r);
		// Set to white
		SDL_SetRenderDrawColor(renderer, 255,255,255, 255);

		Text::Draw("NEW HIGH SCORE!", IntVector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 64), FONT::ID::GOLD, FONT::ALLIGNMENT::CENTER);
		Text::Draw("Enter Your Name:", IntVector2D(SCREEN_WIDTH/2, SCREEN_HEIGHT/2-32), FONT::ID::REGULAR, FONT::ALLIGNMENT::CENTER);

		// Draw individual name characters
		for (int i = 0; i < 3; i++)
		{
			if (i == selectedLetter)
			{
				Text::Draw(std::string{ enteredName[i] }, IntVector2D(SCREEN_WIDTH/2+(32*(-1 + i)), SCREEN_HEIGHT/2), FONT::ID::GOLD, FONT::ALLIGNMENT::CENTER);
			}
			else {
				Text::Draw(std::string{ enteredName[i] }, IntVector2D(SCREEN_WIDTH/2+(32*(-1+i)), SCREEN_HEIGHT / 2), FONT::ID::SILVER, FONT::ALLIGNMENT::CENTER);
			}
		}

		Text::Draw("Arrows/WASD: Select", IntVector2D(16, (SCREEN_HEIGHT / 2) + 32), FONT::ID::REGULAR, FONT::ALLIGNMENT::LEFT);
		Text::Draw("Submit: Z", IntVector2D(SCREEN_WIDTH-16, (SCREEN_HEIGHT / 2) + 32), FONT::ID::REGULAR, FONT::ALLIGNMENT::RIGHT);
	}
}

void ScoreNameEntryWindow::IncrementLetterCharacter(int amount) {
	//Increment the selected character's ASCII value by the given amount
	int new_letter_code = (int)enteredName[selectedLetter];
	new_letter_code += amount;

	// Loop letters back around if character value is out of range
	if (new_letter_code > CHARACTER_RANGE.y) 
	{
		new_letter_code = CHARACTER_RANGE.x;
	}
	else if (new_letter_code < CHARACTER_RANGE.x) {
		new_letter_code = CHARACTER_RANGE.y;
	}

	enteredName[selectedLetter] = (char)new_letter_code;
}

void ScoreNameEntryWindow::SwitchLetter(int increment) {
	selectedLetter = (selectedLetter + increment);

	// Clamp between 0 and 2
	if (selectedLetter > 2) {
		selectedLetter = 0;
	}
	if (selectedLetter < 0)
	{
		selectedLetter = 2;
	}
}