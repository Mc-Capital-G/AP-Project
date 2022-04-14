#pragma once
#include "includeSDL.h"

class Window {
public:
	SDL_Renderer* gameRenderer;
	SDL_Window* gameWindow;
	Window();
	~Window();
	bool init(int screenWidth, int screenHeight);
private:
};