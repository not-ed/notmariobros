#pragma once
#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <fstream>

#define SCORE_FILE_PATH "Data/Score/highscores.nmb"
#define SCORE_TABLE_SIZE 10

struct HighScoreData {
	std::string name[SCORE_TABLE_SIZE];
	int score[SCORE_TABLE_SIZE];

	std::string GetName(int position) {
		if (position >= 0 && position <= SCORE_TABLE_SIZE-1)
		{
			return name[position].substr(0,3);
		}
		else return "N/A"; // Return an unexpected value to indicate an error.
	}
	
	int GetScore(int position) {
		if (position >= 0 && position <= SCORE_TABLE_SIZE-1)
		{
			return score[position];
		}
		else return -1; // Return an unexpected value to indicate an error.
	}
};

namespace HighScore {

	// Anonymous namespace - Only accessible to things already inside the HighScore namespace
	namespace {
		HighScoreData CreateFreshDataFile();
		void WriteScoreFileData(HighScoreData score_data);
	}

	HighScoreData GetLatestHighscore();
	void SubmitScoreEntry(const char name[3], int score);
}

#endif