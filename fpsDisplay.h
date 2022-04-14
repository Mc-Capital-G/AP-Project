#pragma once
#include "font.h"
#include "timer.h"
#include <sstream>

class fpsDisplay {
public:
	fpsDisplay();
	void calculate();
	font text;
	std::stringstream fpsText;
private:
	int countedFrames = 0;
	float avgFPS;
	timer frameCounter;
};



