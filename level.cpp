#include "level.h"

level::level(SDL_Renderer* ren) {
	renderer = ren;
	enemies = {};
	currentWaveNum = 0;
	totalWaves = 5;
	enemiesPerWave = 10;
	initEnemies(enemiesPerWave);
}

void level::initEnemies(int enemyNum) {
	int prevPosX = 70;
	int prevPosY = 100;
	for (int i = 0; i <= enemyNum; i++) {
		enemies.emplace_back(new enemy);
		if (prevPosX + 60 > 500) {
			prevPosX = 70;
			prevPosY += 40;
		}
		enemies[i]->init(renderer);
		enemies[i]->posX = prevPosX + 60;
		enemies[i]->posY = prevPosY;
		prevPosX = enemies[i]->posX;
	}
}

level::~level() {
	enemies.clear();
	enemies.~vector();
}