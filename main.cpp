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
		timer inputTimer;
		inputTimer.start();

		font startGame("assets/PublicPixel-0W5Kv.ttf", 50), startOptions("assets/PublicPixel-0W5Kv.ttf", 30), credits("assets/PublicPixel-0W5Kv.ttf", 30);

		int menuOption = 0;

		renderObj stars[2];
		stars[1].posY = -800;
		for (int i = 0; i < 2; i++) {
			stars[i].createTexture("assets/stars.png", window.gameRenderer);
		}

		renderObj menuSelect;
		menuSelect.createTexture("assets/border.png", window.gameRenderer);

		while (!handler.quit) {

			handler.handle();

			if (inputTimer.getTicks() > 75) {
				if (handler.keyState[SDL_SCANCODE_UP] || handler.keyState[SDL_SCANCODE_W]) menuOption--;
				if (handler.keyState[SDL_SCANCODE_DOWN] || handler.keyState[SDL_SCANCODE_S]) menuOption++;
				if (menuOption > 2) menuOption = 0;
				if (menuOption < 0) menuOption = 2;
				inputTimer.start();
			}

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

			SDL_RenderClear(window.gameRenderer); // clear previously rendered frame from renderer 
			SDL_SetRenderDrawColor(window.gameRenderer, 0x00, 0x00, 0x00, 0xFF); // set the default renderer color to make the background a different color
			for (int i = 0; i < 2; i++) {
				stars[i].posY++;
				if (stars[i].posY > 800) stars[i].posY = -800;
				stars[i].render(window.gameRenderer);
			}

			startGame.display("START GAME", window.gameRenderer, 300 - startGame.width / 2, 400 - startGame.height / 2);
			startOptions.display("OPTIONS", window.gameRenderer, 300 - startOptions.width / 2, 600 - startOptions.width / 2);
			credits.display("CREDITS", window.gameRenderer, 300 - credits.width / 2, 700 - credits.width / 2);

			SDL_RenderPresent(window.gameRenderer);

			if (handler.keyState[SDL_SCANCODE_RETURN]) {
				switch(menuOption) {
				case 0:
					gameLoop(&window); // start game
					break;
				case 1:
					break;
				case 2:
					break;
				}
			}
		}
	}

	closeSDL();
	return 0;
}