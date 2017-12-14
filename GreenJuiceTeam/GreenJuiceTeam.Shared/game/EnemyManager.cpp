#include "EnemyManager.h"
#include "TMXLoader.h"

EnemyManager* EnemyManager::instance=NULL;

EnemyManager* EnemyManager::getSingleton(){
	if(instance==NULL){
		instance = new 	EnemyManager();
	}
	return instance;
}

EnemyManager::~EnemyManager(){
	deinit();
}
void EnemyManager::deinit(){
	enemies.clear();
}

void EnemyManager::addEnemy(TMXLoader* tmxLoader, Enemy::ENEMY_TYPE enemyType, Enemy::DIRECTION type, int x, int y){
	Enemy* e=new Enemy(tmxLoader,enemyType, type, x, y);
	enemies.push_back(e);
}


void EnemyManager::draw(){
	for(int i=0;i<enemies.size();i++){
		if(enemies[i]->isAlive)
			enemies[i]->draw();
	}
}

void EnemyManager::update(float deltaTime){
	for(int i=0;i<enemies.size();i++){
		if(!enemies[i]->dieing && enemies[i]->isAlive)
			enemies[i]->update(deltaTime);
	}
}

bool EnemyManager::collide(int x, int y){
	for(int i=0;i<enemies.size();i++){
		if(!enemies[i]->dieing && enemies[i]->isAlive){
			if(enemies[i]->tileX==x && enemies[i]->tileY==y){
				return true;
			}
		}
	}
	return false;
}

Enemy* EnemyManager::checkForDeath(int x, int y){
	for(int i=0;i<enemies.size();i++){
		if(enemies[i]->isAlive){
			if(enemies[i]->tileX==x && enemies[i]->tileY==y){
				//__android_log_print(ANDROID_LOG_INFO, "adMOB","inimigo %d morreu\n", i);
				enemies[i]->isAlive=false;
				return enemies[i];
			}
		}
	}
	return NULL;
}
