#include "includeSDL.h"
#include "inputHandler.h"


inputHandler::inputHandler() {
	quit = false;
	keyState = NULL;
	pressedKeys = {};
}

inputHandler::~inputHandler() {
	quit = NULL;
	keyState = NULL;
}

std::vector<int>* inputHandler::handle() {
	SDL_Event event;
	SDL_PollEvent(&event);
	keyState = SDL_GetKeyboardState(NULL);
	switch(event.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			pressedKeys.clear();
			for (int i = 0; i < sizeof(keyState); i++) {
				if (keyState[i]) {
					pressedKeys.emplace_back(keyState[i]);
				}
			}
		default: break;
	}

	for (int i = 0; i < pressedKeys.size(); i++) {
		printf("%d", pressedKeys[i]);
	}
	return &pressedKeys;
}