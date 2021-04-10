#pragma once
#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <fstream>

#define SCORE_FILE_PATH "Data/Score/highscores.nmb"
#define SCORE_TABLE_SIZE 10

// A packet of data that contains both the relevant names and scores read from the high scores file which can be indexed into to retrieve the desired information.
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

	// Potentially destructive functions, such as erasing file data are held in an Anonymous namespace.
	// Anonymous namespaces are only accessible to things already inside the HighScore namespace
	namespace {
		// Generate (or wipe over the existing one if it exists due to truncation) a fresh High Score data file.
		HighScoreData CreateFreshDataFile();

		// Write the contents of a HighScoreData packet to file
		void WriteScoreFileData(HighScoreData score_data);
	}

	// Pull down the latest high score from file.
	HighScoreData GetLatestHighscore();

	// Submit a score to the table, and then write changes to the disk.
	void SubmitScoreEntry(const char name[3], int score);
}

#endif