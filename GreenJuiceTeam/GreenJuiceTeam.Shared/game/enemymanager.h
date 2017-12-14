#pragma once
#include <vector>
#include "Enemy.h"

class TMXLoader;

class EnemyManager{

	public:

		void update(float deltaTime);
		void draw();

		void addEnemy(TMXLoader* tmxLoader, Enemy::ENEMY_TYPE enemyType, Enemy::DIRECTION type, int x, int y);

		Enemy* checkForDeath(int, int);

		bool collide(int, int);

		void deinit();
		~EnemyManager();
		static EnemyManager* getSingleton();



	private:
		EnemyManager(){
		}
		static EnemyManager* instance;
		std::vector<Enemy*> enemies;

};