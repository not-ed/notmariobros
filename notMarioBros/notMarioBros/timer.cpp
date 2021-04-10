#include "timer.h"

void Timer::Update(float delta_time) {
	if (!expired)
	{
		remainingTime -= delta_time;
		if (remainingTime <= 0.0f)
		{
			expired = true;
		}
	}
}

void Timer::Reset() {
	remainingTime = startingTime;
	expired = false;
}

void Timer::SetTime(float new_time, bool reset) {
	startingTime = new_time;
	if (reset)
	{
		Reset();
	}
}