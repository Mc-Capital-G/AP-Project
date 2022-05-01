#include "gameLoop.h"

// this is the actual game

void gameLoop(Window* window) {

	renderObj stars[2];
	stars[1].posY = -800;
	for (int i = 0; i < 2; i++) {
		stars[i].createTexture("assets/stars.png", window->gameRenderer);
	}


	inputHandler handler;

	level level(window->gameRenderer);

	fpsDisplay FPS("assets/PublicPixel-0W5Kv.ttf", 15); // initalize the FPS display 
	
	font stats("assets/PublicPixel-0W5Kv.ttf", 15); // initialize the font and system used to display stats on the screen

	// create and initialize player
	player player(window->gameRenderer);

	while (!handler.quit) {
		
		//handle input and move the player accordingly
		handler.handle(); // get keyboard state
		if (handler.keyState[SDL_SCANCODE_W] || handler.keyState[SDL_SCANCODE_UP]) player.move(UP);
		if (handler.keyState[SDL_SCANCODE_D] || handler.keyState[SDL_SCANCODE_RIGHT]) player.move(RIGHT);
		if (handler.keyState[SDL_SCANCODE_A] || handler.keyState[SDL_SCANCODE_LEFT]) player.move(LEFT);
		if (handler.keyState[SDL_SCANCODE_S] || handler.keyState[SDL_SCANCODE_DOWN]) player.move(DOWN);
		if (handler.keyState[SDL_SCANCODE_RETURN] || handler.keyState[SDL_SCANCODE_SPACE]) player.fire(); // shoot a laser
		
		for (int i = 0; i < level.enemies.size(); i++) level.enemies[i]->move(); // move enemies

		player.handleBullets(); 

		// check for collision between enemies and bullets
		std::vector<enemy*>::iterator enemyPtr = level.enemies.begin();
		for (int i = 0; i < level.enemies.size(); i++) {
			bool stop = false;
			std::vector<bullet*>::iterator bulletPtr = player.bullets.begin();
			for (int j = 0; j < player.bullets.size(); j++) {
				if (level.enemies[i]->posX <= player.bullets[j]->posX && level.enemies[i]->posX + level.enemies[i]->width >= player.bullets[j]->posX && level.enemies[i]->posY <= player.bullets[j]->posY && level.enemies[i]->posY + level.enemies[i]->height >= player.bullets[j]->posY) {
					if (level.enemies[i]->handleHit()) {
						player.score += level.enemies[i]->pointVal;
						delete level.enemies[i];
						level.enemies.erase(enemyPtr);
						stop = true;
					}
					delete player.bullets[j];
					player.bullets.erase(bulletPtr);
					break;
				}
				std::advance(bulletPtr, 1);
			}
			if (stop) break;
			std::advance(enemyPtr, 1);
		}


		// rendering context -> render things that need to be rendered. 
		// Objects called to be rendered at the bottom of the list will be rendered last and therefore will be "on top"
		SDL_RenderClear(window->gameRenderer); // clear previously rendered frame from renderer 
		SDL_SetRenderDrawColor(window->gameRenderer, 0x00, 0x00, 0x00, 0xFF); // set the default renderer color to make the background a different color
		
		// move and render background
		for (int i = 0; i < 2; i++) {
			stars[i].posY++;
			stars[i].render(window->gameRenderer);
			if (stars[i].posY > 800) stars[i].posY = -800;
		}

		for (int i = 0; i < level.enemies.size(); i++) level.enemies[i]->render(window->gameRenderer); // render enemies

		for (int i = 0; i < player.bullets.size(); i++) player.bullets[i]->render(window->gameRenderer); // render bullets

		player.render(window->gameRenderer); // render player

		FPS.calculate(window->gameRenderer); // calculate and display framerate
		stats.display(player.getStats(), window->gameRenderer, 0, 775); // display player stats
		SDL_RenderPresent(window->gameRenderer); // render to window
	}
}