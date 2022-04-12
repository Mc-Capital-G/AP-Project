#include "gameLoop.h"

void gameLoop(Window* window) {
	SDL_RenderClear(window->gameRenderer);

	SDL_RenderPresent(window->gameRenderer);
	SDL_Delay(5000);
}