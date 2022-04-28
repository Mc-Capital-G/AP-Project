#include "font.h"

font::font(std::string path, int fontSize) {
	fontType = TTF_OpenFont(path.c_str(), fontSize);
	color = { 0xFF, 0xFF, 0xFF };
}

bool font::createTex(std::string renderText, SDL_Renderer* renderer) {
	SDL_Surface* loadedSurface = TTF_RenderText_Solid(fontType, renderText.c_str(), color);
	if (loadedSurface == NULL) {
		printf("Text could not be loaded into a texture. SDL Error: %s\n", SDL_GetError());
		return NULL;
	}
	else {
		SDL_Texture* newTex = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (newTex == NULL) {
			printf("Texture could not be created from text. SDL Error: %s\n", SDL_GetError());
			return NULL;
		}
		else {
			width = loadedSurface->w;
			height = loadedSurface->h;
			SDL_SetTextureBlendMode(newTex, SDL_BLENDMODE_BLEND);
			SDL_FreeSurface(loadedSurface);
			tex = newTex;
		}
	}
	return tex != NULL;
}

void font::display(std::string renderText, SDL_Renderer* renderer, int x, int y) {
	posX = x;
	posY = y;
	createTex(renderText, renderer);
	render(renderer);
	SDL_DestroyTexture(tex); // do not delete this line ever - without it tex eats memory instantly
}