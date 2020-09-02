#include <SDL.h>

#ifndef TIMER_H
#define	TIMER_H

class Timer
{
public:
	//Initializes variables
	Timer();

	//The various clock actions
	void Start();
	void Stop();
	void Pause();
	void UnPause();

	//Gets the timer's time
	double GetTime();

	//Checks the status of the timer
	bool IsStarted();
	bool IsPaused();

private:
	//The clock time when the timer started
	Uint32 startTicks;

	//The ticks stored when the timer was paused
	Uint32 pausedTicks;

	//The timer status
	bool paused;
	bool started;
};

#endif /* TIMER_H */