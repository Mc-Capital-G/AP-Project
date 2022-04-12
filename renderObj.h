#pragma once
#include "includeSDL.h"

class renderObj {
public:
	renderObj();
	~renderObj();
	void createTexture(std::string path, SDL_Renderer* renderer);
	void render(SDL_Renderer* renderer);
	SDL_Texture* tex;
	SDL_Rect* clip;
	int width;
	int height;
	double posX;
	double posY;
private:
};

