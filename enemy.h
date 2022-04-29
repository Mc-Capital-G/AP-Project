#pragma once
#include "renderObj.h"

class enemy : public renderObj {
public:
	enemy(SDL_Renderer* renderer);
	void move();
	bool handleHit();
	int pointVal;
private:
	SDL_Color color;
	int hp;
	int dmg;
	float speed;
	float distMoved;
};

