#include "score.h"
#include <iostream>

namespace HighScore {

	// Anonymous namespace - Only accessible to things already inside the HighScore namespace
	namespace {

		// Generate (or wipe over the existing one if it exists due to truncation) a fresh High Score data file.
		HighScoreData CreateFreshDataFile() {
			std::ofstream outFile;
			HighScoreData data;

			outFile.open("Data/Score/highscores.nmb", std::ios::trunc);

			std::cout << "Generating new score file..." << std::endl;

			if (outFile.is_open())
			{
				for (int i = 0; i < SCORE_TABLE_SIZE; i++)
				{
					outFile << "--- ";
					outFile << 0 << "\n";
					data.name[i] = "---";
					data.score[i] = 0;
				}
			}

			outFile.close();
			return data;
		}

		// Overwrite the high score file with the entire contents of a HighScoreData object
		void WriteScoreFileData(HighScoreData score_data) {
			std::ofstream outFile;

			outFile.open(SCORE_FILE_PATH, std::ios::trunc);

			if (outFile.is_open())
			{
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
			for (int i = 0; i < SCORE_TABLE_SIZE; i++)
			{
				scoreFile >> data.name[i];
				scoreFile >> data.score[i];
			}
			scoreFile.close();
		}
		else {
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
}