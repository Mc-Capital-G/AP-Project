#pragma once
#include "renderObj.h"
#include "enums.h"
#include <sstream>
#include "bullet.h"
#include <vector>

class player : public renderObj {
public:
	player(SDL_Renderer* renderer);
	void move(int direction);
	std::string getStats();
	std::vector<bullet*> bullets;
	void fire();
private:
	int lives;
	int score;
	int hp;
	int dmg;
	int speed;
	int bulletType;
	SDL_Renderer* pointToRen;
};

