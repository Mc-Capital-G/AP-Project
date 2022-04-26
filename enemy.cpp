#include "enemy.h"

enemy::enemy() {
	posX = 300 - (width / 3);
	posY = 100;
	color = { 0xFF, 0x00, 0xFF };
	hp = 5;
	dmg = 2;
	//SDL_SetTextureColorMod(tex, color.r, color.g, color.b);
}

void enemy::init(SDL_Renderer* renderer) {
	createTexture("assets/enemy.png", renderer);
}

void enemy::move() {

}

bool enemy::handleHit() {
	//hp--;
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
		return 1;
	default:
		color = { 0x00, 0x00, 0x00 };
		break;
	}
	SDL_SetTextureColorMod(tex, color.r, color.g, color.b);
	
	return 0;
}