#include "includeSDL.h"
#include "inputHandler.h"


inputHandler::inputHandler() {
	quit = false;
	keyState = NULL;
	pressedKeys = {0};
}

inputHandler::~inputHandler() {
	quit = NULL;
	keyState = NULL;
}

std::vector<int> inputHandler::handle() {
	pressedKeys.clear();
	SDL_Event event;
	SDL_PollEvent(&event);
	keyState = SDL_GetKeyboardState(NULL);
	switch(event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		default: 
			for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
				if (keyState[i]) {
					pressedKeys.emplace_back(i);
				}
			}
			break;
	}
	return pressedKeys;
}