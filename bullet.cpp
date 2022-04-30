#include "bullet.h"
#include "enums.h"

bullet::bullet(int bulletType, int x, int y, SDL_Renderer* renderer) {
	createTexture("assets/bullet.png", renderer);
	type = bulletType;
	posX = x;
	posY = y;
	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
	switch (type) {
	case NORMAL:
		dmg = 1;
		speed = 10;
		color = { 0xFF, 0x00, 0x00 };
		break;
	case BOMB:
		dmg = 5;
		speed = 5;
		break;
	case ENEMY:
		dmg = 1;
		speed = 10;
		color = { 0x00, 0xFF, 0x00 };
		break;
	}
	SDL_SetTextureColorMod(tex, color.r, color.g, color.b);
}

void bullet::move() {
	posY -= speed;
}