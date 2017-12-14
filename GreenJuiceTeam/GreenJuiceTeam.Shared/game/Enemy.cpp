#include "Enemy.h"
#include "TMXLoader.h"

Enemy::Enemy(TMXLoader* _tmxLoader, Enemy::ENEMY_TYPE enemyType_, DIRECTION type, int x_, int y_){
	enemyType=enemyType_;
	tmxLoader=_tmxLoader;
	shooter=false;

	if(type==LEFT || type==RIGHT){
		direction=type;
		player_state=MOVING_HORIZONTAL;
	}else if(type==UP || type==DOWN){ 
		direction=type;
		player_state=MOVING_VERTICAL;
	}else{
		switch(type){
		case STOP_DOWN:
			direction=DOWN;
			break;
		case STOP_UP:
			direction=UP;
			break;
		case STOP_LEFT:
			direction=LEFT;
			break;
		case STOP_RIGHT:
			direction=RIGHT;
			break;
		}
		player_state=STOPPED;
	}

	x=x_*92;
	y=y_*92;
	tileX=x_;
	tileY=y_;
	stepX=0;
	stepY=0;
	isAlive=true;

	calculateNextMove(false);

	switch(enemyType){
	case ENEMY_1:
		glLoadTileSet("inimigo01-baixo.png",sprDown,92,92,512,128);  
		glLoadTileSet("inimigo01-cima.png",sprUp,92,92,512,128);  
		glLoadTileSet("inimigo01-direita.png",sprRight,92,92,512,128);  
		//glLoadTileSet("inimigo01-esquerda.png",sprLeft,92,92,512,128);  
		glLoadTileSet("inimigo01-morre.png",sprDie,92,92,1024,128);  		
		break;
	case ENEMY_2:
		glLoadTileSet("inimigo02-baixo.png",sprDown,92,92,512,128);  
		glLoadTileSet("inimigo02-cima.png",sprUp,92,92,512,128);  
		glLoadTileSet("inimigo02-direita.png",sprRight,92,92,512,128);   
		//glLoadTileSet("inimigo02-esquerda.png",sprLeft,92,92,512,128);  
		glLoadTileSet("inimigo02-morre.png",sprDie,92,92,1024,128);  
		break;
	case ENEMY_3:
		glLoadTileSet("inimigo03-baixo.png",sprDown,92,92,512,128);  
		glLoadTileSet("inimigo03-cima.png",sprUp,92,92,512,128);  
		glLoadTileSet("inimigo03-direita.png",sprRight,92,92,512,128);  
		//glLoadTileSet("inimigo03-esquerda.png",sprLeft,92,92,512,128);  
		glLoadTileSet("inimigo02-morre.png",sprDie,92,92,1024,128);   
		glLoadTileSet("inimigo03-tiro.png",sprShoot,92,92,512,128);   		
		shooter=true;
		break;
	default:
		glLoadTileSet("inimigo01-baixo.png",sprDown,92,92,512,128);  
		glLoadTileSet("inimigo01-cima.png",sprUp,92,92,512,128);  
		glLoadTileSet("inimigo01-direita.png",sprRight,92,92,512,128);  
		//glLoadTileSet("inimigo01-esquerda.png",sprLeft,92,92,512,128);  
		glLoadTileSet("inimigo01-morre.png",sprDie,92,92,1024,128);  		
		break;
	}

	animationCounter=0;
	shootCounter=0;
	frames=0;
	shootFrames=0;
	dieing=false;
	active=false;

}

Enemy::~Enemy(){
	//delete[] sprLeft;
	//delete[] sprRight;
	//delete[] sprUp;
	//delete[] sprDown;

	//delete[] sprDie;
}


void Enemy::draw(){
	frames++;	

	if(!dieing){
		if(frames%15==0){
			animationCounter++;
		}
		if(animationCounter>3){
			animationCounter=0;
		}

		switch(direction){
		case LEFT:
			glSprite(x,y,4,&sprRight[animationCounter]);
			break;
		case RIGHT:
			glSprite(x,y,0,&sprLeft[animationCounter]);
			break;
		case UP:
			glSprite(x,y,0,&sprUp[animationCounter]);
			break;
		case DOWN:
			glSprite(x,y,0,&sprDown[animationCounter]);		
			break;
		}
	}else{
		if(frames%15==0){
			animationCounter++;
		}
		if(animationCounter>10){
			animationCounter=10;
			isAlive=false;
		}
		glSprite(x,y,0,&sprDie[animationCounter]);
	}

	if(active){
		if(frames%9==0){
			shootCounter++;
		}
		if(shootCounter>4){
			shootCounter=0;
		}
		glSprite(shootX,shootY,0,&sprShoot[shootCounter]);
	}

}

void Enemy::update(int deltaTime){
	//__android_log_print(ANDROID_LOG_INFO, "adMOB","enemy update 01 %d",shootFrames);
	if(!isAlive)
		return;

	switch(player_state){
	case MOVING_HORIZONTAL:
		//__android_log_print(ANDROID_LOG_INFO, "adMOB","enemy update 02");
		if((int)stepX<(int)x){
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","enemy update 03");
			direction=LEFT;
			x-=deltaTime;
		}
		else if((int)stepX>(int)x){
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","enemy update 04");
			direction=RIGHT;
			x+=deltaTime;
		}
		else{
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","enemy update 05");
			dieing=!arrival();
		}
		break;
	case MOVING_VERTICAL:
		//__android_log_print(ANDROID_LOG_INFO, "adMOB","enemy update 06");
		if((int)stepY<(int)y){
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","enemy update 07");
			direction=UP;
			y-=deltaTime;
		}
		else if((int)stepY>(int)y){
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","enemy update 08");
			direction=DOWN;
			y+=deltaTime;
		}
		else{
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","enemy update 09");
			dieing=!arrival();
		}
		break;
	default:
		//__android_log_print(ANDROID_LOG_INFO, "adMOB","enemy update 10");
		break;
	}

	if(shooter && !active){
		shootFrames++;
		if(shootFrames%180==0){
			shootX=x;
			shootY=y;
			active=true;
			shootCounter=0;
		}		
	}

	if(active)
		shoot(2);
	//__android_log_print(ANDROID_LOG_INFO, "adMOB","enemy update 11");
}

void Enemy::calculateNextMove(bool secondTime){
	int nextX=tileX;
	int nextY=tileY;

	//__android_log_print(ANDROID_LOG_INFO, "adMOB","x00");
	if(direction==UP){
		//__android_log_print(ANDROID_LOG_INFO, "adMOB","x01");
		if(tmxLoader->isPassable(tileX,tileY-1)){
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","x02");
			nextY--;
			updateDestination(nextX, nextY);
		}else{
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","x03");
			if(!secondTime){
				//__android_log_print(ANDROID_LOG_INFO, "adMOB","x04");
				animationCounter=0;
				direction=DOWN;
				calculateNextMove(true);
			}
			else{
				//__android_log_print(ANDROID_LOG_INFO, "adMOB","to preso :P");
			}
		}
	}

	else if(direction==DOWN){
		//__android_log_print(ANDROID_LOG_INFO, "adMOB","x05");
		if(tmxLoader->isPassable(tileX,tileY+1)){
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","x06");
			nextY++;
			updateDestination(nextX, nextY);
		}else{
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","x07");
			if(!secondTime){
				//__android_log_print(ANDROID_LOG_INFO, "adMOB","x08");
				animationCounter=0;
				direction=UP;
				calculateNextMove(true);
			}
			else{
				//__android_log_print(ANDROID_LOG_INFO, "adMOB","to preso :P");
			}
		}
	}

	else if(direction==RIGHT){
		//__android_log_print(ANDROID_LOG_INFO, "adMOB","x09");
		if(tmxLoader->isPassable(tileX+1,tileY)){
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","x10");
			nextX++;
			updateDestination(nextX, nextY);
		}else{
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","x11");
			if(!secondTime){
				//__android_log_print(ANDROID_LOG_INFO, "adMOB","x12");
				animationCounter=0;
				direction=LEFT;
				calculateNextMove(true);
			}
			else{
				//__android_log_print(ANDROID_LOG_INFO, "adMOB","to preso :P");
			}
		}
	}

	else if(direction==LEFT){
		//__android_log_print(ANDROID_LOG_INFO, "adMOB","x13");
		if(tmxLoader->isPassable(tileX-1,tileY)){
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","x14");
			nextX--;
			updateDestination(nextX, nextY);
		}else{
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","x15");
			if(!secondTime){
				//__android_log_print(ANDROID_LOG_INFO, "adMOB","x16");
				animationCounter=0;
				direction=RIGHT;
				calculateNextMove(true);
			}
			else{
				//__android_log_print(ANDROID_LOG_INFO, "adMOB","to preso :P");
			}
		}
	}
}

void Enemy::updateDestination(int nextX, int nextY){
	stepX=nextX*92;
	stepY=nextY*92;
	//__android_log_print(ANDROID_LOG_INFO, "adMOB","updateDestination %d %d %f %f", nextX, nextY, stepX, stepY);
}


bool Enemy::arrival(){
	tileX=(int)(stepX+46)/92;
	tileY=(int)(stepY+46)/92;

	x=tileX*92;
	y=tileY*92;

	if(tmxLoader->isHole(tileX,tileY)){
		//__android_log_print(ANDROID_LOG_INFO, "adMOB","Enemy is dead!");
		frames=0;
		animationCounter=0;
		return false;
	}else{
		//__android_log_print(ANDROID_LOG_INFO, "adMOB","calculateNextMove()");
		calculateNextMove(false);
	}

	return true;

}

void Enemy::shoot(int deltaTime){
	switch(direction){
	case LEFT:
		shootX-=deltaTime;
		break;
	case DOWN:
		shootY+=deltaTime;
		break;
	case RIGHT:
		shootX+=deltaTime;
		break;
	case UP:
		shootY-=deltaTime;
		break;
	}

	shootTileX=(int)(shootX+46)/92;
	shootTileY=(int)(shootY+46)/92;
	if(shootTileY>4 || shootTileX>7 || shootTileX<0 || shootTileY<0 || !tmxLoader->isPassable(shootTileX,shootTileY)){
		//die(false);
		active=false;
		shootFrames=0;
	}
}


