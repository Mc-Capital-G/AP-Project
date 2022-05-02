#include "level.h"

level::level(SDL_Renderer* ren) {
	renderer = ren;
	enemies = {};
	bullets = {};
	levelNum = 1;
	currentWaveNum = 0;
	totalWaves = 0;
	enemiesPerWave = 12;
	gameOver = false;
	start = false;
	waveSetup = false;
	displayLevel = false;
}

void level::initEnemies(int enemyNum) {
	int prevPosX = 70;
	int prevPosY = -300;
	for (int i = 0; i < enemyNum; i++) {
		enemies.emplace_back(new enemy(renderer));
		if ((prevPosX + enemies[i]->width) + 60 > 500) {
			prevPosX = 70;
			prevPosY += 40;
		}
		enemies[i]->posX = prevPosX + 60;
		enemies[i]->posY = prevPosY;
		prevPosX = enemies[i]->posX;
	}
}

void level::handleBullets() {
	if (!bullets.empty()) {
		std::vector<bullet*>::iterator ptr = bullets.begin();
		for (int i = 0; i < bullets.size(); i++) {
			bullets[i]->move();
			if (bullets[i]->posY > 800) {
				delete bullets[i];
				bullets.erase(ptr);
				break;
			}
			std::advance(ptr, 1);
		}
	}
}

std::string level::getLevel() {
	std::stringstream text;
	text << "LEVEL " << levelNum;
	return text.str();
}

void level::init() {
	waveSetup = false;
	totalWaves = levelNum;
	enemiesPerWave = 10 + levelNum * 2;
	initEnemies(enemiesPerWave);
	start = true;
}

void level::advance() {
	currentWaveNum++;
	if (currentWaveNum > totalWaves) {
		currentWaveNum = 0;
		levelNum++;
		start = false;
		return;
	}
	waveSetup = false;
	initEnemies(enemiesPerWave);
}

level::~level() {
	enemies.clear();
	enemies.~vector();
}