#include "gameLoop.h"

// this is the actual game

void gameLoop(Window* window, inputHandler* handler) {

	renderObj stars[2];
	stars[1].posY = -800;
	for (int i = 0; i < 2; i++) {
		stars[i].createTexture("assets/stars.png", window->gameRenderer);
	}

	level level(window->gameRenderer);
	
	font stats("assets/PublicPixel-0W5Kv.ttf", 20); // initialize the font and system used to display stats on the screen

	// create and initialize player
	player player(window->gameRenderer);

	while (!handler->quit) {
		
		//handle input and move the player accordingly
		handler->handle(); // get keyboard state
		if (handler->keyState[SDL_SCANCODE_W] || handler->keyState[SDL_SCANCODE_UP]) player.move(UP);
		if (handler->keyState[SDL_SCANCODE_D] || handler->keyState[SDL_SCANCODE_RIGHT]) player.move(RIGHT);
		if (handler->keyState[SDL_SCANCODE_A] || handler->keyState[SDL_SCANCODE_LEFT]) player.move(LEFT);
		if (handler->keyState[SDL_SCANCODE_S] || handler->keyState[SDL_SCANCODE_DOWN]) player.move(DOWN);
		if (handler->keyState[SDL_SCANCODE_RETURN] || handler->keyState[SDL_SCANCODE_SPACE]) player.fire(); // shoot a laser

		// pause menu
		if (handler->keyState[SDL_SCANCODE_ESCAPE]) {
			int menuOpt = 0;
			bool unpause = false;
			font text("assets/PublicPixel-0W5Kv.ttf", 20);
			do {
				handler->handle();
				if (handler->keyState[SDL_SCANCODE_W] || handler->keyState[SDL_SCANCODE_UP]) menuOpt--;
				if (handler->keyState[SDL_SCANCODE_S] || handler->keyState[SDL_SCANCODE_DOWN]) menuOpt++;
				if (handler->keyState[SDL_SCANCODE_RETURN] || handler->keyState[SDL_SCANCODE_SPACE]) unpause = true;
				if (menuOpt > 1) menuOpt = 1;
				if (menuOpt < 0) menuOpt = 0;

				switch (menuOpt) {
				case 0:
					text.color = { 0xFF, 0xFF, 0x00 };
					text.display("RESUME", window->gameRenderer, 230, 300);
					text.color = { 0xFF, 0xFF, 0xFF };
					text.display("QUIT", window->gameRenderer, 255, 350);
					break;
				case 1:
					text.color = { 0xFF, 0xFF, 0xFF };
					text.display("RESUME", window->gameRenderer, 230, 300);
					text.color = { 0xFF, 0xFF, 0x00 };
					text.display("QUIT", window->gameRenderer, 255, 350);
					break;
				}
				SDL_RenderPresent(window->gameRenderer);
				
			} while (!unpause && !handler->quit);
			handler->inputTimer.start();
			if (menuOpt == 1) return;
		}
		
		// move and handle enemies
		for (int i = 0; i < level.enemies.size(); i++) {
			level.enemies[i]->move();
			if (level.enemies[i]->fireTimer.getTicks() >= level.enemies[i]->nextShot * 1000) {
				level.bullets.emplace_back(level.enemies[i]->fire(window->gameRenderer));
				std::default_random_engine generator;
				std::uniform_int_distribution<int> distributor(1, 10);
				level.enemies[i]->nextShot = distributor(generator);
			}
		}

		player.handleBullets(); // handle bullet movement and remove bullets if needed
		level.handleBullets(); // handle enemy bullets

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
		for (int i = 0; i < level.bullets.size(); i++) level.bullets[i]->render(window->gameRenderer); // render enemy bullets

		player.render(window->gameRenderer); // render player

		stats.display(player.getScore(), window->gameRenderer, 225, 0); // display player score
		stats.display(player.getLives(), window->gameRenderer, 225, 775); // display player lives
		SDL_RenderPresent(window->gameRenderer); // render to window
	}
}