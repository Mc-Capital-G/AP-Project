#include "fpsDisplay.h"

fpsDisplay::fpsDisplay() {
	text = new font("assets/PublicPixel-0W5Kv.ttf", 25);
	frameCounter.start();
	text->color = { 0xFF, 0xFF, 0xFF };
	text->posX = 0;
	text->posY = 0;
	avgFPS = 0;
}

void fpsDisplay::calculate(SDL_Renderer* renderer) { // function that calculates framerate and sets the display texture
	avgFPS = countedFrames / (frameCounter.getTicks() / 1000.f);
	if (avgFPS > 2000000) {
		avgFPS = 0;
	}

	fpsText.str("");
	std::string fpsOLD = std::to_string(avgFPS);
	if (fpsOLD != fpsText.str()) {
		fpsText << "FPS:" << (round(avgFPS));
	}
	countedFrames++;

	text->createTex(fpsText.str(), renderer);
	text->render(renderer);
}
