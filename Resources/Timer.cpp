#include "Timer.h"

Timer::Timer()
{
	//Initialize the variables
	startTicks = 0;
	pausedTicks = 0;

	paused = false;
	started = false;
}

void Timer::Start()
{
	//Start the timer
	started = true;

	//UnPause the timer
	paused = false;

	//Get the current clock time
	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void Timer::Stop()
{
	//Stop the timer
	started = false;

	//UnPause the timer
	paused = false;

	//Clear tick variables
	startTicks = 0;
	pausedTicks = 0;
}

void Timer::Pause()
{
	//If the timer is running and isn't already paused
	if (started && !paused)
	{
		//Pause the timer
		paused = true;

		//Calculate the paused ticks
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void Timer::UnPause()
{
	//If the timer is running and paused
	if (started && paused)
	{
		//UnPause the timer
		paused = false;

		//Reset the Starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset the paused ticks
		pausedTicks = 0;
	}
}

double Timer::GetTime()
{
	//The actual timer time
	double time = 0.0;

	//If the timer is running
	if (started)
	{
		//If the timer is paused
		if (paused)
		{
			//Return the number of ticks when the timer was paused
			time = (double)pausedTicks;
		}
		else
		{
			//Return the current time minus the Start time
			time = (double)(SDL_GetTicks() - startTicks);
		}
	}

	return time;
}

bool Timer::IsStarted()
{
	//Timer is running and paused or unpaused
	return started;
}

bool Timer::IsPaused()
{
	//Timer is running and paused
	return paused && started;
}