#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include "SDL_timer.h"

class Timer
{
	private:
		void* v;

		const Uint32 TIMER_TYPE = SDL_USEREVENT;
		const int DEFAULT_STARTING_SPEED = 1000;

		SDL_TimerID id;
	public:
		Timer();
		Timer(int speed);
		Uint32 eventType();
		void stop();
		void restart();
		void restart(int newSpeed);
};

#endif // TIMER_H
