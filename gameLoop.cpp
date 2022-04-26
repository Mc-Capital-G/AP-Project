#include "gameLoop.h"
#include "inputHandler.h"
#include "renderObj.h"
#include "timer.h"
#include "font.h"
#include <sstream>
#include "fpsDisplay.h"
#include "enemy.h"
#include "player.h"

// this is the actual game

void gameLoop(Window* window) {

	// global objects and variables
	inputHandler handler;

	fpsDisplay FPS;

	int enemyNum = 15;

	std::vector<enemy*> enemies = {};

	for (int i = 0; i <= enemyNum; i++) {
		enemies.emplace_back(new enemy);
		enemies[i]->init(window->gameRenderer);
		enemies[i]->posX = 100 + (30 * i);
		enemies[i]->posY = 200;
	}

	player player;
	player.init(window->gameRenderer);

	while (!handler.quit) {
		
		handler.handle();
		if (handler.keyState[SDL_SCANCODE_W]) player.move(UP);
		if (handler.keyState[SDL_SCANCODE_D]) player.move(RIGHT);
		if (handler.keyState[SDL_SCANCODE_A]) player.move(LEFT);
		if (handler.keyState[SDL_SCANCODE_S]) player.move(DOWN);

		FPS.calculate();
		

		// rendering context 
		SDL_RenderClear(window->gameRenderer); // clear previously rendered frame from renderer 
		SDL_SetRenderDrawColor(window->gameRenderer, 0x00, 0x00, 0x00, 0xFF);

		FPS.text.createTex(FPS.fpsText.str(), window->gameRenderer); // create the texture for the fps
		FPS.text.render(window->gameRenderer); // render the fps 

		for(int i = 0; i < enemies.size(); i++) {
			enemies[i]->render(window->gameRenderer);
		}
		
		player.render(window->gameRenderer);
		SDL_RenderPresent(window->gameRenderer); // render to window
		SDL_DestroyTexture(FPS.text.tex); // do not delete this line ever - without it fpsDisplay.tex eats memory instantly

	}
}