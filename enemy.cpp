#include "enemy.h"

enemy::enemy(SDL_Renderer* renderer) {
	posX = 300 - (width / 3);
	posY = 100;
	color = { 0xFF, 0x00, 0xFF };
	hp = 5;
	dmg = 1;
	speed = 0.5;
	distMoved = 0;
	createTexture("assets/enemy.png", renderer);
	pointVal = 100;
	fireTimer.start();
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distributor(1, 10);
	nextShot = distributor(generator);
}

void enemy::move() { // makes enemies move back and forth on the screen
	if (distMoved < 50) {
		posX += speed;
		distMoved += speed;
	}
	else if (distMoved < 150) {
		posX -= speed;
		distMoved += speed;
	}
	else if (distMoved < 200) {
		posX += speed;
		distMoved += speed;
	}
	else distMoved = 0;
}

bool enemy::handleHit() {
	hp--;
	switch (hp) {
	case 5:
		color = { 0xFF, 0x00, 0xFF };
		break;
	case 4:
		color = { 0xFF, 0x00, 0xC8 };
		break;
	case 3:
		color = { 0xFF, 0x00, 0x96 };
		break;
	case 2:
		color = { 0xFF, 0x00, 0x64 };
		break;
	case 1:
		color = { 0xFF, 0x00, 0x00 };
		break;
	case 0:
		return true;
	default:
		color = { 0x00, 0x00, 0x00 };
		break;
	}
	SDL_SetTextureColorMod(tex, color.r, color.g, color.b);
	return false;
}

bullet* enemy::fire(SDL_Renderer* renderer) {
	fireTimer.start();
	bullet* ptr = new bullet(ENEMY, posX + width/2, posY, renderer);
	return ptr;
}