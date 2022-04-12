#include "closeSDL.h"

void closeSDL() {
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}