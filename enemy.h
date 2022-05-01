#pragma once
#include "renderObj.h"
#include "bullet.h"
#include "timer.h"
#include "enums.h"
#include <random>

class enemy : public renderObj {
public:
	enemy(SDL_Renderer* renderer);
	void move();
	bool handleHit();
	bullet* fire(SDL_Renderer* renderer);
	int pointVal;
	timer fireTimer;
	int nextShot;
private:
	SDL_Color color;
	int hp;
	int dmg;
	float speed;
	float distMoved;
};

