#pragma once
#include "enemy.h"
#include "bullet.h"
#include <sstream>
#include <vector>
#include <iterator>
#include <random>

class level {
public:
	level(SDL_Renderer* ren);
	~level();
	std::vector<enemy*> enemies;
	std::vector<bullet*> bullets;
	void handleBullets();
	std::string getLevel();
	void init();
	void advance();
	bool gameOver;
	bool start;
	bool waveSetup;
	bool displayLevel;
	int currentWaveNum;
	int enemyFireSpeed;
private:
	void initEnemies(int enemyNum);
	SDL_Renderer* renderer;
	int levelNum;
	int enemiesPerWave;
	int totalWaves;
};

