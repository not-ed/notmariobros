#pragma once
#ifndef TIMER_H
#define TIMER_H

// Class for the management of a passing sequence of time which can then be tied to game events by checking its state.
class Timer
{
public:
	void Update(float delta_time);
	
	// Reset the timer
	void Reset();

	// Set a new time for the timer object, and optionally reset it once changed.
	void SetTime(float new_time, bool reset); 

	// Has the timer run out or activated?
	bool IsExpired() { return expired; }

	// Return how much time is remaining until the timer expires
	float RemainingTime() { return remainingTime; }
private:
	// Whether the timer has run out or not
	bool expired = true; 

	// Initial value set to when timer is reset.
	float startingTime = 0.0f;
	// Time left until expiration/activation.
	float remainingTime = 0.0f;
};

#endif