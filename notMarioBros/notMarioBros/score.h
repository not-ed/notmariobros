#pragma once
#ifndef SCORE_H
#define SCORE_H

#include "SDL.h"
#include "constants.h"
#include "commons.h"
#include "textrenderer.h"
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

// An encapsulation of a integer used for keeping track of game score with convenience functions
struct ScoreCounter {
	int currentScore;

	void Reset() {
		currentScore = 0;
	}

	void Add(int amount) {
		currentScore += amount;
	}

	void Add(int amount, float multiplier) {
		currentScore += (amount * multiplier);
	}

	int GetCurrentScore() {
		return currentScore;
	}
};

// A pop up window that allows the player to enter a 3-character name which can be fetched from the object to be used for submitting high score entries.
class ScoreNameEntryWindow
{
public:

	void Update(float delta_time, SDL_Event e);
	void Render();
	
	void Display() { displayed = true; }
	bool IsDisplayed() { return displayed; }

	// Return the name submitted in the window
	std::string GetEnteredName() { return enteredName; }

	void SetRenderer(SDL_Renderer* game_renderer) { renderer = game_renderer; }

private:
	// Is the window currently being shown?
	bool displayed = false;

	// Range of ASCII character values that can be selected for entering a name
	const IntVector2D CHARACTER_RANGE = IntVector2D(33, 126);
	int startingCharacterValue = 65; // 'A' 'A' 'A'

	char enteredName[3] = { (char)startingCharacterValue, (char)startingCharacterValue, (char)startingCharacterValue };
	// Current letter being edited
	int selectedLetter = 0;

	SDL_Renderer* renderer = nullptr;

	void IncrementLetterCharacter(int amount);
	void SwitchLetter(int increment);

	void Close() { displayed = false; }
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

	// Check if a given score is eligible for addition to the high score table.
	bool NewScoreAchieved(int score);
}

#endif