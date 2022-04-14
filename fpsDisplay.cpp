#include "fpsDisplay.h"

fpsDisplay::fpsDisplay() {

	frameCounter.start();
	text.color = { 0xFF, 0xFF, 0xFF };
	text.posX = 0;
	text.posY = -10;
	text.init("assets/Lato-Black.ttf", 50);
}

void fpsDisplay::calculate() { // function that calculates framerate and sets the display texture
	avgFPS = countedFrames / (frameCounter.getTicks() / 1000.f);
	if (avgFPS > 2000000) {
		avgFPS = 0;
	}

	fpsText.str("");
	std::string fpsOLD = std::to_string(avgFPS);
	if (fpsOLD != fpsText.str()) {
		printf("%f", avgFPS);
		fpsText << round(avgFPS);
	}
	countedFrames++;
}
