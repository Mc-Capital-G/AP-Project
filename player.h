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
	std::string getScore();
	std::string getLives();
	std::vector<bullet*> bullets;
	void fire();
	void handleBullets();
	void getHit();
	bool respawn();
	timer respawnTimer;
	bool alive;
	int score;
private:
	int lives;
	int speed;
	int bulletType;
	SDL_Renderer* pointToRen;
	timer fireTimer;
};

