#undef main
#include "includeSDL.h"
#include "window.h"
#include "closeSDL.h"
#include "gameLoop.h"

// This program is built using the SDL Library, which makes creating and rendering images, sound, and text to our window possible.
// Some code has been adapted from Lazy Foo Productions's online tutorials at https://lazyfoo.net/tutorials/SDL/

int main(int argc, char* argv[]) {
	
	// initialize SDL and its window, go to game loop if successfully initialized.

	Window window;
	if (!window.init(600, 800)) {
		return 1;
	}
	else {
		inputHandler handler;
		handler.inputTimer.start();

		font startGame("assets/PublicPixel-0W5Kv.ttf", 50), startOptions("assets/PublicPixel-0W5Kv.ttf", 30), credits("assets/PublicPixel-0W5Kv.ttf", 30);
		font text("assets/PublicPixel-0W5Kv.ttf", 20);

		int menuOption = 0;
		int menu = 0;

		renderObj stars[2];
		stars[1].posY = -800;
		for (int i = 0; i < 2; i++) {
			stars[i].createTexture("assets/stars.png", window.gameRenderer);
		}

		renderObj logo;
		logo.createTexture("assets/logo.png", window.gameRenderer);
		logo.posX = 300 - logo.width/2;
		logo.posY = 50;

		Mix_Music* theme = Mix_LoadMUS("assets/theme.wav"); // initialize sound file

		bool select = false;

		while (!handler.quit) {
			select = false;

			if (Mix_PlayingMusic() == 0) {
				Mix_PlayMusic(theme, -1);
			}

			// get input
			handler.handle();
			if (handler.inputTimer.getTicks() > 100) {
				if (handler.keyState[SDL_SCANCODE_UP] || handler.keyState[SDL_SCANCODE_W]) menuOption--;
				if (handler.keyState[SDL_SCANCODE_DOWN] || handler.keyState[SDL_SCANCODE_S]) menuOption++;
				if (handler.keyState[SDL_SCANCODE_RETURN] || handler.keyState[SDL_SCANCODE_SPACE]) select = true;
				if (menuOption > 2) menuOption = 0;
				if (menuOption < 0) menuOption = 2;
				handler.inputTimer.start();
			}

			// show which menu option is selected by changing text color of option
			switch (menuOption) {
			case 0:
				startGame.color = { 0xFF, 0xFF, 0x00 };
				startOptions.color = { 0xFF, 0xFF, 0xFF };
				credits.color = { 0xFF, 0xFF, 0xFF };
				break;
			case 1:
				startGame.color = { 0xFF, 0xFF, 0xFF };
				startOptions.color = { 0xFF, 0xFF, 0x00 };
				credits.color = { 0xFF, 0xFF, 0xFF };
				break;
			case 2:
				startGame.color = { 0xFF, 0xFF, 0xFF };
				startOptions.color = { 0xFF, 0xFF, 0xFF };
				credits.color = { 0xFF, 0xFF, 0x00 };
				break;
			}

			//handle input

			if (select) {
				if (menu == 0) {
					switch (menuOption) {
					case 0: // start game
						Mix_HaltMusic();
						gameLoop(&window, &handler);
						break;
					case 1: // go to controls
						menu = 1;
						break;
					case 2: // credits
						menu = 2;
						break;
					}
				}
				else {
					menu = 0;
				}
			}

			SDL_RenderClear(window.gameRenderer); // clear previously rendered frame from renderer 
			SDL_SetRenderDrawColor(window.gameRenderer, 0x00, 0x00, 0x00, 0xFF); // set the default renderer color to make the background a different color
			for (int i = 0; i < 2; i++) {
				stars[i].posY++;
				if (stars[i].posY > 800) stars[i].posY = -800;
				stars[i].render(window.gameRenderer);
			}

			switch (menu) {
			case 0: // main menu
				startGame.display("START GAME", window.gameRenderer, 300 - startGame.width / 2, 500 - startGame.height / 2);
				startOptions.display("CONTROLS", window.gameRenderer, 300 - startOptions.width / 2, 700 - startOptions.width / 2);
				credits.display("CREDITS", window.gameRenderer, 300 - credits.width / 2, 775 - credits.width / 2);
				logo.render(window.gameRenderer);
				break;
			case 1: // controls menu
				text.display("W/UP -> MOVE UP", window.gameRenderer, 50, 200);
				text.display("A/LEFT -> MOVE LEFT", window.gameRenderer, 50, 250);
				text.display("S/DOWN -> MOVE DOWN", window.gameRenderer, 50, 300);
				text.display("D/RIGHT -> MOVE RIGHT", window.gameRenderer, 50, 350);
				text.display("ENTER/SPACE -> FIRE", window.gameRenderer, 50, 400);
				text.display("PRESS ENTER TO GO BACK", window.gameRenderer, 50, 500);
				break;
			case 2: // credits menu
				text.display("CREATED BY", window.gameRenderer, 200, 200 );
				text.display("DECLAN MCGRELLIS", window.gameRenderer, 135, 225 );
				text.display("POWERED BY SDL2", window.gameRenderer, 145, 300 );
				text.display("ALL SOUNDS LICENSED BY", window.gameRenderer, 80, 375 );
				text.display("YOUTUBE'S CREATIVE COMMONS", window.gameRenderer, 40, 400 );
				text.display("PRESS ENTER TO GO BACK", window.gameRenderer, 80, 500 );
				break;
			}
			SDL_RenderPresent(window.gameRenderer);
		}
	}

	closeSDL();
	return 0;
}