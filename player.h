#pragma once
#include "renderObj.h"
#include "enums.h"

class player : public renderObj {
public:
	player(SDL_Renderer* renderer);
	void move(int direction);
private:
	int hp;
	int dmg;
	int speed;
};

