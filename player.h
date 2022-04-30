#pragma once
#include "renderObj.h"
#include "enums.h"
#include <sstream>
#include "bullet.h"
#include <vector>
#include "timer.h"

class player : public renderObj {
public:
	player(SDL_Renderer* renderer);
	void move(int direction);
	std::string getStats();
	std::vector<bullet*> bullets;
	void fire();
	void handleBullets();
	int score;
private:
	int lives;
	int hp;
	int dmg;
	int speed;
	int bulletType;
	SDL_Renderer* pointToRen;
	timer fireTimer;
};

