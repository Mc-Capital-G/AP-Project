#include "gameLoop.h"
#include "inputHandler.h"
#include "renderObj.h"
#include "timer.h"
#include "font.h"
#include <sstream>
#include "fpsDisplay.h"
#include "player.h"
#include "level.h"

// this is the actual game

void gameLoop(Window* window) {

	// global objects and variables
	inputHandler handler;

	fpsDisplay FPS;

	level level(window->gameRenderer);
	

	// create and initialize player
	player player(window->gameRenderer);

	while (!handler.quit) {
		
		//handle input and move the player accordingly
		handler.handle();
		if (handler.keyState[SDL_SCANCODE_W]) player.move(UP);
		if (handler.keyState[SDL_SCANCODE_D]) player.move(RIGHT);
		if (handler.keyState[SDL_SCANCODE_A]) player.move(LEFT);
		if (handler.keyState[SDL_SCANCODE_S]) player.move(DOWN);

		FPS.calculate(); // calculate framerate
		
		for (int i = 0; i < level.enemies.size(); i++) level.enemies[i]->move();

		// rendering context -> render things that need to be rendered. 
		// Objects called to be rendered at the bottom of the list will be rendered last and therefore will be "on top"
		SDL_RenderClear(window->gameRenderer); // clear previously rendered frame from renderer 
		SDL_SetRenderDrawColor(window->gameRenderer, 0x00, 0x00, 0x00, 0xFF); // set the default renderer color to make the background a different color

		FPS.text.createTex(FPS.fpsText.str(), window->gameRenderer); // create the texture for the fps
		FPS.text.render(window->gameRenderer); // render the fps 

		for (int i = 0; i < level.enemies.size(); i++) {
			level.enemies[i]->render(window->gameRenderer);
		}
		
		player.render(window->gameRenderer);
		SDL_RenderPresent(window->gameRenderer); // render to window
		SDL_DestroyTexture(FPS.text.tex); // do not delete this line ever - without it FPS.tex eats memory instantly
	}
}