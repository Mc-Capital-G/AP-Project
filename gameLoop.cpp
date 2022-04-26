#include "gameLoop.h"
#include "inputHandler.h"
#include "renderObj.h"
#include "timer.h"
#include "font.h"
#include <sstream>
#include "fpsDisplay.h"
#include "enemy.h"

// this is the actual game

void gameLoop(Window* window) {

	// global objects and variables
	inputHandler handler;

	fpsDisplay FPS;


	renderObj testSquare;
	testSquare.createTexture("assets/square.png", window->gameRenderer);
	testSquare.posX = 300 - (testSquare.width/2);
	testSquare.posY = 400 - (testSquare.height / 2);

	std::vector<enemy> enemies = {};

	while (!handler.quit) {
		handler.handle();

		FPS.calculate();
		

		// rendering context 
		SDL_RenderClear(window->gameRenderer); // clear previously rendered frame from renderer 
		SDL_SetRenderDrawColor(window->gameRenderer, 0x00, 0x00, 0x00, 0xFF);

		FPS.text.createTex(FPS.fpsText.str(), window->gameRenderer); // create the texture for the fps
		FPS.text.render(window->gameRenderer); // render the fps 

		testSquare.render(window->gameRenderer);
		SDL_RenderPresent(window->gameRenderer); // render to window
		SDL_DestroyTexture(FPS.text.tex); // do not delete this line ever - without it fpsDisplay.tex eats memory instantly

	}
}