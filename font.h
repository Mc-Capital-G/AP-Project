#pragma once
#include "includeSDL.h"
#include "renderObj.h"

class font : public renderObj {
public:
	font(std::string path, int fontSize);
	bool createTex(std::string renderText, SDL_Renderer* renderer);
	void display(std::string renderText, SDL_Renderer* renderer, int x, int y);
	TTF_Font* fontType;
	SDL_Color color;
};

