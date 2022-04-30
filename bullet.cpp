#include "bullet.h"
#include "enums.h"

bullet::bullet(int bulletType, int x, int y, SDL_Renderer* renderer) {
	createTexture("assets/bullet.png", renderer);
	type = bulletType;
	posX = x;
	posY = y;
	switch (type) {
	case NORMAL:
		dmg = 1;
		speed = 10;
		break;
	case BOMB:
		dmg = 5;
		speed = 5;
		break;
	case ENEMY:
		dmg = 1;
		speed = 10;
		break;
	}
}

void bullet::move() {
	posY -= speed;
}