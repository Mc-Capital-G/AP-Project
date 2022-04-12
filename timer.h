#pragma once
#include "includeSDL.h"

class timer {
public:
	timer();
	void start();
	void stop();
	void pause();
	void unpause();
	Uint32 getTicks();
private:
	Uint32 startTicks;
	Uint32 pausedTicks;
	bool started;
	bool paused;
};

