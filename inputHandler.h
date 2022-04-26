#pragma once
#include "window.h"
#include <vector>

class inputHandler {
public:
	inputHandler();
	~inputHandler();
	std::vector<int> handle();
	bool quit;
	const Uint8* keyState;
private:
	std::vector<int> pressedKeys;
};