#pragma once
#include "TMXLoader.h"
#include "core/gl2d.h"




class Fireball{


	public:
		enum STATE{
			LEFT,
			RIGHT,
			DOWN,
			UP
		};

		Fireball(TMXLoader*);
		~Fireball();
		void draw();
		void update(int deltaTime);
		void activate(int x,int y, STATE _state);
		bool active;
		bool dieing;
		bool enemy;

		int tileX;
		int tileY;

		void die(bool enemy,int enemyX=0,int enemyY=0);


	private:
		float x;
		float y;
		
		STATE state;
		TMXLoader* tmxLoader;

		
		glImage spr[5];
		glImage spr2[11];
		glImage spr3[10];

		int frames;
		int sprFrame;
		int spr3Frame;

		int enemyX;
		int enemyY;
		

};