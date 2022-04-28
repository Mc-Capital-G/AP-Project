#pragma once
#include "includeSDL.h"
#include "renderObj.h"

class font : public renderObj {
public:
	font(std::string path, int fontSize);
	bool createTex(std::string renderText, SDL_Renderer* renderer);
	TTF_Font* fontType;
	SDL_Color color;
};

