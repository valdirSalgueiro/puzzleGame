#pragma once

#include <stdio.h>
#include "core/gl2d.h"

class TMXLoader;

class Enemy{

	public:
		enum STATE{
			MOVING_HORIZONTAL,
			MOVING_VERTICAL,
			STOPPED
		};

		enum DIRECTION{
			LEFT,
			RIGHT,
			UP,
			DOWN,
			STOP_LEFT,
			STOP_RIGHT,
			STOP_UP,
			STOP_DOWN,
		};



		enum ENEMY_TYPE{
			ENEMY_1,
			ENEMY_2,
			ENEMY_3,
		};


		Enemy(TMXLoader* tmxLoader, Enemy::ENEMY_TYPE enemyType, DIRECTION type, int x, int y);
		~Enemy();
		void update(int deltaTime);
		void draw();
		void calculateNextMove(bool);
		void updateDestination(int nextX, int nextY);
		bool arrival();

		void shoot(int deltaTime);

		int tileX;
		int tileY;

		STATE player_state;
		DIRECTION direction;
		ENEMY_TYPE enemyType;
		bool isAlive;
		bool dieing;

		float x;
		float y;

		float shootX;
		float shootY;

		float shootTileX;
		float shootTileY;

		bool active;

	private:


		float stepX;
		float stepY;
		TMXLoader* tmxLoader;
		

		int animationCounter;
		int shootCounter;

		glImage sprLeft[5];
		glImage sprRight[5];
		glImage sprUp[5];
		glImage sprDown[5];
		glImage sprDie[11];
		glImage sprShoot[5];
		

		

		int frames;
		int shootFrames;
		bool shooter;



};