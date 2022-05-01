#pragma once
#include "enemy.h"
#include "bullet.h"
#include <vector>
#include <iterator>

class level {
public:
	level(SDL_Renderer* ren);
	~level();
	std::vector<enemy*> enemies;
	std::vector<bullet*> bullets;
	void handleBullets();
private:
	void initEnemies(int enemyNum);
	SDL_Renderer* renderer;
	int levelNum;
	int currentWaveNum;
	int enemiesPerWave;
	int totalWaves;
};

