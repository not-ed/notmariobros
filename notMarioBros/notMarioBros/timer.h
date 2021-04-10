#pragma once
#ifndef TIMER_H
#define TIMER_H

// Class for the management of a passing sequence of time which can then be tied to game events by checking its state.
class Timer
{
public:
	void Update(float deltaTime);
	void Reset(); // Reset the timer
	void SetTime(float new_time, bool reset); // Set a new time for the timer object, and optionally reset it once changed.
	bool IsExpired() { return expired; } // Has the timer run out or activated?
	float RemainingTime() { return remainingTime; }
private:
	bool expired = true; // The timer has run out.
	float startingTime = 0.0f; // Initial value set to when timer is reset.
	float remainingTime = 0.0f; // Time left until expiration/activation.
};

#endif