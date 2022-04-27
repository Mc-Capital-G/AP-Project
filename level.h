#pragma once
#include "enemy.h"
#include <vector>

class level {
public:
	level(SDL_Renderer* ren);
	~level();
	
private:
	void initEnemies(int enemyNum);
	SDL_Renderer* renderer;
	std::vector<enemy*> enemies;
	int levelNum;
	int currentWaveNum;
	int enemiesPerWave;
	int totalWaves;
};

