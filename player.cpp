#include "player.h"

player::player(SDL_Renderer* renderer) {
	score = 0;
	lives = 3;
	hp = 3;
	dmg = 1;
	speed = 5;
	createTexture("assets/playerNew.png", renderer);
	posY = 725;
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
	if (posX > 550 - width) {
		posX = 550 - width;
	}
	if (posX < 50) {
		posX = 50;
	}
	if (posY < 525) {
		posY = 525;
	}
	if (posY > 725) {
		posY = 725;
	}
}

std::string player::getStats() {
	std::stringstream text; 
	text << "SCORE:" << score << " HP:" << hp << " LIVES:" << lives;
	return text.str();
}