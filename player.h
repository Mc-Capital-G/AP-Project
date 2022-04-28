#pragma once
#include "renderObj.h"
#include "enums.h"
#include <sstream>

class player : public renderObj {
public:
	player(SDL_Renderer* renderer);
	void move(int direction);
	std::string getStats();
private:
	int lives;
	int score;
	int hp;
	int dmg;
	int speed;
};

