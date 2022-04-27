#pragma once
#include "enemy.h"
#include <vector>

class level {
public:
	level(SDL_Renderer* ren);
	~level();
	std::vector<enemy*> enemies;
private:
	void initEnemies(int enemyNum);
	SDL_Renderer* renderer;
	int levelNum;
	int currentWaveNum;
	int enemiesPerWave;
	int totalWaves;
};

