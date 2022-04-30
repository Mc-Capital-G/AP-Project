#pragma once
#include "renderObj.h"

class bullet : public renderObj {
public:
	bullet(int bulletType, int x, int y, SDL_Renderer* renderer);
	void move();
	int dmg;
	int type;
private:
	int speed;
	SDL_Color color = { 0xFF, 0xFF, 0xFF };
};