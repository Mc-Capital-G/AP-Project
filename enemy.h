#pragma once
#include "renderObj.h"

class enemy : public renderObj {
public:
	enemy();
	void init(SDL_Renderer* renderer);
	void move();
	bool handleHit();
private:
	SDL_Color color;
	int hp;
	int dmg;
	float speed;
	float distMoved;
};

