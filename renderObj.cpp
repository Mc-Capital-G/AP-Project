#include "renderObj.h"

renderObj::renderObj() {
	tex = NULL;
	posX = NULL;
	posY = NULL;
	width = NULL;
	height = NULL;
	clip = NULL;
}

renderObj::~renderObj() {
	SDL_DestroyTexture(tex);
}

void renderObj::createTexture(std::string path, SDL_Renderer* renderer) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("%s could not be loaded. SDL Error: %s\n", path.c_str(), SDL_GetError());
	}
	else {
		SDL_Texture* newTex = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTex == NULL) {
			printf("Texture could not be created from %s. SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else {
			width = loadedSurface->w;
			height = loadedSurface->h;
			SDL_SetTextureBlendMode(newTex, SDL_BLENDMODE_BLEND);
			SDL_FreeSurface(loadedSurface);
			tex = newTex;
		}
	}
}

void renderObj::render(SDL_Renderer* renderer) {
	SDL_Rect target = { posX, posY, width, height };
	SDL_RenderCopy(renderer, tex, clip, &target);
}

