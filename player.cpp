#include "player.h"

player::player(SDL_Renderer* renderer) {
	hp = 3;
	dmg = 1;
	speed = 5;
	createTexture("assets/playerNew.png", renderer);
	posY = 750;
	posX = 300 - (width / 2);
}

void player::move(int direction) {
	switch (direction) {
	case UP:
		posY -= speed;
		break;
	case LEFT:
		posX -= speed;
		break;
	case RIGHT:
		posX += speed;
		break;
	case DOWN:
		posY += speed;
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