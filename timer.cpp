#include "timer.h"

timer::timer() {
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

void timer::start() {
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void timer::stop() {
	started = false;
	paused = false;
	startTicks = 0;
	pausedTicks = 0;
}

void timer::pause() {
	if (started && !paused) {
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void timer::unpause() {
	if (started && paused) {
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

Uint32 timer::getTicks() {
	Uint32 time = 0;
	if (started) {
		if (paused) {
			time = pausedTicks;
		}
		else {
			time = SDL_GetTicks() - startTicks;
		}
	}
	return time;
}