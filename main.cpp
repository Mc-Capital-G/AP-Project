#undef main
#include "includeSDL.h"
#include "window.h"
#include "closeSDL.h"
#include "gameLoop.h"

// This program is built using the SDL Library, which makes creating and rendering images, sound, and text to our window possible.
// Some code has been adapted from Lazy Foo Productions's online tutorials at https://lazyfoo.net/tutorials/SDL/

int main(int argc, char* argv[]) {
	
	// initialize SDL and its window, go to game loop if successfully initialized.

	Window window;
	if (!window.init()) {
		return 1;
	}
	else {
		gameLoop(&window);
	}

	closeSDL();
	return 0;
}