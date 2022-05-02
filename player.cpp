#include "player.h"

player::player(SDL_Renderer* renderer) {
	score = 0;
	lives = 3;
	speed = 5;
	createTexture("assets/playerNew.png", renderer);
	posY = 725;
	posX = 300 - (width / 2);
	bulletType = NORMAL;
	bullets = {};
	pointToRen = renderer;
	fireTimer.start();
	alive = true;
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

std::string player::getScore() {
	std::stringstream text; 
	text << "SCORE " << score;
	return text.str();
}

std::string player::getLives() {
	std::stringstream text;
	text << "LIVES " << lives;
	return text.str();
}

void player::fire() {
	if (fireTimer.getTicks() > 100) {
		bullets.emplace_back(new bullet(bulletType, (posX + width / 2), posY, pointToRen));
		fireTimer.start();
	}
}

void player::handleBullets() {
	if (!bullets.empty()) {
		std::vector<bullet*>::iterator ptr = bullets.begin();
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->move();
			if (bullets[i]->posY < 0) {
				delete bullets[i];
				bullets.erase(ptr);
				break;
			}
			std::advance(ptr, 1);
		}
	}
}

void player::getHit() {
	alive = false;
	posX = -100;
	posY = -100;
	respawnTimer.start();
}

bool player::respawn() {
	if (lives > 0) {
		alive = true;
		posX = 300 - width / 2;
		posY = 725;
		lives--;
	}
	respawnTimer.start();
	respawnTimer.pause();
	return alive;
}