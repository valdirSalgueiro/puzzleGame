#include "fireball.h"

Fireball::Fireball(TMXLoader* _tmxLoader){
	tmxLoader=_tmxLoader;

	x=0;
	y=0;
	frames=0;
	sprFrame=0;
	spr3Frame=0;
	active=false;
	dieing=false;
	enemy=false;

	glLoadTileSet("fogo-player.png",spr,92,92,512,128);  
	glLoadTileSet("fogo-colide.png",spr2,92,92,1024,128);  
	glLoadTileSet("morre-fogo.png",spr3,92,92,512,256);  	
}

Fireball::~Fireball(){
}


void Fireball::draw(){
	if(active){
		if(frames%15==0){
			sprFrame++;
			}
		if(sprFrame>4){
			sprFrame=0;
		}
		switch(state){
		case LEFT:
			glSprite(x,y,0,&spr[sprFrame]);
			break;
		case DOWN:
			glSprite(x,y,0,&spr[sprFrame]);
			break;
		case RIGHT:
			glSprite(x,y,0,&spr[sprFrame]);
			break;
		case UP:
			glSprite(x,y,GL2D_FLIP_V,&spr[sprFrame]);
			break;
		}

		
	}else{
		if(dieing){
			if(frames%7==0){
				sprFrame++;
			}
			if(sprFrame>6){
				dieing=false;
			}
			glSprite(x,y,0,&spr2[sprFrame]);
		}

		if (enemy){
			if(frames%10==0){
				spr3Frame++;
			}
			if(spr3Frame==4){
				spr3Frame=5;
			}
			if(spr3Frame>7){
				enemy=false;
			}
			glSprite(enemyX,enemyY,0,&spr3[spr3Frame]);
		}


	}

}

void Fireball::activate(int _x,int _y, STATE _state){
	state=_state;
	active=true;
	sprFrame=0;

	switch(state){
	case LEFT:
		//_x-=1;
		break;
	case DOWN:
		//_y+=1;
		break;
	case RIGHT:
		//_x+=1;
		break;
	case UP:
		//_y-=1;
		break;
	}

	x=_x*92;
	y=_y*92;	
}

void Fireball::die(bool _enemy,int enemyX_,int enemyY_){
	enemyX=enemyX_;
	enemyY=enemyY_;
	sprFrame=0;
	dieing=true;
	active=false;

	enemy=_enemy;
	if(enemy){
		spr3Frame=0;
	}
}

void Fireball::update(int deltaTime){
	frames++;
	if(active){
		switch(state){
		case LEFT:
			x-=deltaTime;
			break;
		case DOWN:
			y+=deltaTime;
			break;
		case RIGHT:
			x+=deltaTime;
			break;
		case UP:
			y-=deltaTime;
			break;
		}

		tileX=(int)(x+46)/92;
		tileY=(int)(y+46)/92;
		//__android_log_print(ANDROID_LOG_INFO, "adMOB", "[00]");
		if(tileY>4 || tileX>7 || tileX<0 || tileY<0 || !tmxLoader->isPassable(tileX,tileY)){
			die(false);
		}
		//__android_log_print(ANDROID_LOG_INFO, "adMOB", "[01]");
	}
}