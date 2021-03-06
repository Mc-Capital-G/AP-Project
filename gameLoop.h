#pragma once
#include "includeSDL.h"
#include "window.h"
#include "inputHandler.h"
#include "renderObj.h"
#include "timer.h"
#include "font.h"
#include <sstream>
#include "fpsDisplay.h"
#include "player.h"
#include "level.h"
#include <random>
#include <iterator>


void gameLoop(Window* window, inputHandler* handler);