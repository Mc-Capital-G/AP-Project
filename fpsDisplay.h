#pragma once
#include "font.h"
#include "timer.h"
#include <sstream>

class fpsDisplay {
public:
	fpsDisplay(std::string path, int fontSize);
	void calculate(SDL_Renderer* renderer);
	font* text;
	std::stringstream fpsText;
private:
	int countedFrames = 0;
	float avgFPS;
	timer frameCounter;
};



