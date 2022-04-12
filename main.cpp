#undef main
#include "includeSDL.h"
#include "window.h"
#include "closeSDL.h"

int main(int argc, char* argv[]) {
	Window window;
	if (!window.init()) {
		return 1;
	}
	else {
		SDL_Delay(5000);
	}

	closeSDL();
	return 0;
}