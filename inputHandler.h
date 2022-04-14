#pragma once
#include "window.h"
#include <vector>

class inputHandler {
public:
	inputHandler();
	~inputHandler();
	std::vector<int> handle();
	bool quit;
private:
	const Uint8* keyState;
	std::vector<int> pressedKeys;
};