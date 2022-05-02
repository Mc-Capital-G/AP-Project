#include "gameLoop.h"

// this is the actual game

// top left enemy position - (70, 100)

void gameLoop(Window* window, inputHandler* handler) {
	
	//initialize sound effects
	Mix_Chunk* explosion = Mix_LoadWAV("assets/explosion.wav");
	Mix_Chunk* laser = Mix_LoadWAV("assets/laser.wav");
	Mix_Chunk* gameOver = Mix_LoadWAV("assets/gameOver.wav");
	Mix_Chunk* levelStart = Mix_LoadWAV("assets/levelStart.wav");

	// init background
	renderObj stars[2];
	stars[1].posY = -800;
	for (int i = 0; i < 2; i++) {
		stars[i].createTexture("assets/stars.png", window->gameRenderer);
	}

	level level(window->gameRenderer); // init level
	
	font text("assets/PublicPixel-0W5Kv.ttf", 20); // initialize the font and system used to display stats on the screen

	// create and initialize player
	player player(window->gameRenderer);

	while (!handler->quit) {

		//handle game once the level starts
		if (level.start) {
			level.displayLevel = false;
			//handle input and move the player accordingly
			handler->handle(); // get keyboard state
			if (player.alive) {
				if (handler->keyState[SDL_SCANCODE_W] || handler->keyState[SDL_SCANCODE_UP]) player.move(UP);
				if (handler->keyState[SDL_SCANCODE_D] || handler->keyState[SDL_SCANCODE_RIGHT]) player.move(RIGHT);
				if (handler->keyState[SDL_SCANCODE_A] || handler->keyState[SDL_SCANCODE_LEFT]) player.move(LEFT);
				if (handler->keyState[SDL_SCANCODE_S] || handler->keyState[SDL_SCANCODE_DOWN]) player.move(DOWN);
				if (handler->keyState[SDL_SCANCODE_RETURN] || handler->keyState[SDL_SCANCODE_SPACE]) {
					player.fire(); // shoot a laser
					Mix_PlayChannel(-1, laser, 0);
				}
			}

			// pause menu
			if (handler->keyState[SDL_SCANCODE_ESCAPE] && player.alive) {
				int menuOpt = 0;
				bool unpause = false;
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

			// handle enemies and set random timing for shooting
			if (level.waveSetup) {
				std::default_random_engine randomEngine(SDL_GetTicks());
				for (int i = 0; i < level.enemies.size(); i++) {
					level.enemies[i]->move();
					if (level.enemies[i]->fireTimer.getTicks() >= level.enemies[i]->nextShot * 100 && player.alive) {
						std::uniform_int_distribution<long> distributor(10, 19);
						level.bullets.emplace_back(level.enemies[i]->fire(window->gameRenderer, distributor(randomEngine)));
						Mix_PlayChannel(-1, laser, 0);
					}
				}
			}
			else { // move enemies into position
				for (int i = 0; i < level.enemies.size(); i++) level.enemies[i]->posY += 1.5;
				if(level.currentWaveNum == 0) level.displayLevel = true;
				if (level.enemies[0]->posY >= 100) level.waveSetup = true;
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
							Mix_PlayChannel(-1, explosion, 0);
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

			//if player is alive handle player collision
			if (player.alive) {
				// check for collision between player and enemy bullets
				std::vector<bullet*>::iterator bulletPtr = level.bullets.begin();
				for (int i = 0; i < level.bullets.size(); i++) {
					if (player.posX <= level.bullets[i]->posX && player.posX + player.width >= level.bullets[i]->posX && player.posY <= level.bullets[i]->posY && player.posY + player.height >= level.bullets[i]->posY) {
						delete level.bullets[i];
						level.bullets.erase(bulletPtr);
						player.getHit();
						Mix_PlayChannel(-1, explosion, 0);
						break;
					}
					advance(bulletPtr, 1);
				}
			}
			else {
				// respawn player 
				if (player.respawnTimer.getTicks() > 3000) {
					if (!player.respawn()) {
						level.gameOver = true;
						Mix_PlayChannel(-1, gameOver, 0);
					}
				}
			}


		}
		else { // intialize level 
			level.init();
			Mix_PlayChannel(-1, levelStart, 0);
		}
		
		if (level.enemies.empty()) level.advance();

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

		if (level.displayLevel) text.display(level.getLevel(), window->gameRenderer, 225, 300);

		player.render(window->gameRenderer); // render player 

		// render gameOver text if game has ended
		if (level.gameOver) {
			text.display("GAME OVER", window->gameRenderer, 200, 300);
			text.display(level.getLevel(), window->gameRenderer, 225, 350);
			text.display("PRESS ENTER TO RETURN", window->gameRenderer, 85, 450);
			text.display("TO MENU", window->gameRenderer, 225, 475);
			if (handler->keyState[SDL_SCANCODE_RETURN] || handler->keyState[SDL_SCANCODE_SPACE]) {
				handler->inputTimer.start();
				return;
			}
		}

		text.display(player.getScore(), window->gameRenderer, 200, 0); // display player score
		text.display(player.getLives(), window->gameRenderer, 225, 775); // display player lives
		SDL_RenderPresent(window->gameRenderer); // render to window
		printf("%d\n", level.gameOver);
	}
}