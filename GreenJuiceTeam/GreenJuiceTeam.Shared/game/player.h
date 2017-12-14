#pragma once
#include "TMXLoader.h"
#include "core/gl2d.h"

class Player{

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
			DOWN
		};


		Player(TMXLoader* tmxLoader);
		~Player();
		void update(float deltaTime);
		void move(int _x, int _y);
		void draw();
		void calculateNextMove();
		void updateDestination(int nextX, int nextY);
		bool arrival();
		void die();

		void cleanup();

		int tileX;
		int tileY;
		bool crossWall;
		bool jumpTile;
		bool fireBall;
		bool hasKey;
		STATE player_state;
		DIRECTION direction;

		bool isAlive;

		float x;
		float y;

	private:

		float destX;
		float destY;
		float stepX;
		float stepY;
		TMXLoader* tmxLoader;
		bool changePath;
		float desiredX;
		float desiredY;

		int animationCounter;

		glImage sprLeft[5];
		glImage sprRight[5];
		glImage sprUp[5];
		glImage sprDown[5];

		int frames;



};