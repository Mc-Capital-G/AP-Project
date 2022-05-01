#pragma once
#include "window.h"
#include "timer.h"
#include <vector>

class inputHandler {
public:
	inputHandler();
	~inputHandler();
	std::vector<int> handle();
	bool quit;
	const Uint8* keyState;
	timer inputTimer;
private:
	std::vector<int> pressedKeys;
};