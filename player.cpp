#include "player.h"

player::player() {
	hp = 3;
	dmg = 1;
}

void player::init(SDL_Renderer* renderer) {
	createTexture("assets/playerNew.png", renderer);
	posY = 750;
	posX = 300 - (width / 2);
}

void player::move(int direction) {
	switch (direction) {
	case UP:
		posY -= 10;
		break;
	case LEFT:
		posX -= 10;
		break;
	case RIGHT:
		posX += 10;
		break;
	case DOWN:
		posY += 10;
		break;
	case UPRIGHT:
		posX += 10;
		posY -= 10;
		break;
	case UPLEFT:
		posX -= 10;
		posY -= 10;
		break;
	case DOWNRIGHT:
		posX += 10;
		posY += 10;
		break;
	case DOWNLEFT:
		posX -= 10;
		posY += 10;
		break;
	default:
		break;
	}
	if (posX > 590 - width) {
		posX = 590 - width;
	}
	if (posX < 10) {
		posX = 10;
	}
	if (posY < 650) {
		posY = 650;
	}
	if (posY > 750) {
		posY = 750;
	}
}