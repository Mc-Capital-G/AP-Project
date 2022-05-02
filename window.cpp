#include "window.h"

//some window init code was written with help and inspiration from Lazy Foo Production's online tutorials at https://lazyfoo.net/tutorials/SDL/

Window::Window() {
	gameWindow = NULL;
	gameRenderer = NULL;
}

Window::~Window() {
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);
	gameWindow = NULL;
	gameRenderer = NULL;
}

bool Window::init(int screenWidth, int screenHeight) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not be initialized. SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else {
		gameWindow = SDL_CreateWindow("Galaxy Raiders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_INPUT_FOCUS);
		if (gameWindow == NULL) {
			printf("SDL Window could not be created. SDL Error: %s\n", SDL_GetError());
			return false;
		}
		else {
			gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gameRenderer == NULL) {
				printf("Renderer could not be created. SDL Error: %s\n", SDL_GetError());
				return false;
			}
			else {
				SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0x00);
				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
				if (IMG_Init(imgFlags) != imgFlags) {
					printf("SDL Image could not be initialized. SDL Error: %s\n", SDL_GetError());
					return false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
					printf("SDL Mixer could not initialize. SDL Error: %s\n", SDL_GetError());
					return false;
				}
				if (TTF_Init() == -1) {
					printf("SDL ttf could not not initialize. SDL Error: %s\n", SDL_GetError());
					return false;
				}
			}
		}
	}
	return true;
}