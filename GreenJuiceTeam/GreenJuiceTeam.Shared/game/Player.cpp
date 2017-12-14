#include "Player.h"

Player::Player(TMXLoader* _tmxLoader){
	tmxLoader=_tmxLoader;

	int tileset_col;
	int tileset_row;

	tileset_col = 0;
	tileset_row = 0;


	x=0;
	y=92;
	tileX=0;
	tileY=1;
	destX=0;
	destY=0;
	stepX=0;
	stepY=0;
	desiredX=0;
	desiredY=0;

	animationCounter=0;


	player_state=STOPPED;
	direction=DOWN;
	crossWall=false;
	jumpTile=false;
	fireBall=false;
	changePath=false;
	hasKey=false;
	isAlive=true;

	glLoadTileSet("player-anda-baixo.png",sprDown,92,92,512,128);  
	glLoadTileSet("player-anda-cima.png",sprUp,92,92,512,128);  
	glLoadTileSet("player-anda-direita.png",sprRight,92,92,512,128);  
	//glLoadTileSet("player-anda-esquerda.png",sprLeft,92,92,512,128);  

	frames=0;

}

void Player::cleanup(){

}

Player::~Player(){
	//__android_log_print(ANDROID_LOG_INFO, "adMOB", "~Player 0");
	//delete[] sprLeft;
	//__android_log_print(ANDROID_LOG_INFO, "adMOB", "~Player 1");
	//delete[] sprRight;
	//__android_log_print(ANDROID_LOG_INFO, "adMOB", "~Player 2");
	//delete[] sprUp;
	//__android_log_print(ANDROID_LOG_INFO, "adMOB", "~Player 3");
	//delete[] sprDown;
}

void Player::draw(){
	//__android_log_print(ANDROID_LOG_INFO, "adMOB", "draw %d %d",frames,animationCounter);
	frames++;
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
		glSprite(x,y,0,&sprRight[animationCounter]);
		break;
	case UP:
		glSprite(x,y,0,&sprUp[animationCounter]);
		break;
	case DOWN:
		glSprite(x,y,0,&sprDown[animationCounter]);		
		break;
	}
	//__android_log_print(ANDROID_LOG_INFO, "adMOB", "draw %d %d %d end",direction, frames,animationCounter);


}

void Player::update(float deltaTime){
	if(!isAlive)
		return;

	switch(player_state){
	case MOVING_HORIZONTAL:
		//__android_log_print(ANDROID_LOG_INFO, "adMOB", "stepX x %d %d",(int)stepX, (int)x);
		if((int)stepX<(int)x){
			direction=LEFT;
			x-=deltaTime;
		}
		else if((int)stepX>(int)x){
			direction=RIGHT;
			x+=deltaTime;
		}
		else{
			//__android_log_print(ANDROID_LOG_INFO, "adMOB", "arrival");
			isAlive=arrival();
		}
		break;
	case MOVING_VERTICAL:
		if((int)stepY<(int)y){
			direction=UP;
			y-=deltaTime;
		}
		else if((int)stepY>(int)y){
			direction=DOWN;
			y+=deltaTime;
		}
		else{
			//__android_log_print(ANDROID_LOG_INFO, "adMOB", "arrival");
			isAlive=arrival();
		}
		break;
	}
}

void Player::move(int _x, int _y){
	//__android_log_print(ANDROID_LOG_INFO, "adMOB", "move %d %d", _x, _y);
	if(player_state==STOPPED){
		//__android_log_print(ANDROID_LOG_INFO, "adMOB", "stopped");
		destX=_x;
		destY=_y;
		calculateNextMove();
	}else{
		if(tmxLoader->isPassable(tileX,tileY)){
			//__android_log_print(ANDROID_LOG_INFO, "adMOB", "moving");
			changePath=true;
			desiredX=_x;
			desiredY=_y;
		}
	}
}

void Player::calculateNextMove(){
	if((int)(destX+46)/92==tileX && (int)(destY+46)/92==tileY){
		player_state=STOPPED;
		if(!changePath){
			return;
		}
	}

	if(changePath){
		destX=desiredX;
		destY=desiredY;
		changePath=false;
	}
	int tempX=(int)destX/92;
	int tempY=(int)destY/92;
	int nextX=tileX;
	int nextY=tileY;
	if(tempY==tileY){
		if(tileX<tempX){
			if(jumpTile){
				nextX+=2;
			}else{
				nextX++;
			}
		}else if (tileX>tempX){
			if(jumpTile){
				nextX-=2;
			}else{
				nextX--;
			}
		}
		if(	tmxLoader->isPassable(nextX,tileY) && !(tileX==nextX && tileY==nextY)){
			tmxLoader->breakFloor(tileX,tileY);
			updateDestination(nextX, nextY);
			//__android_log_print(ANDROID_LOG_INFO, "adMOB", "MOVING_HORIZONTAL");
			frames=0;
			player_state=MOVING_HORIZONTAL;	
		}else{
			if(crossWall){
				updateDestination(nextX, nextY);
				//__android_log_print(ANDROID_LOG_INFO, "adMOB", "MOVING_HORIZONTAL");
				frames=0;
				player_state=MOVING_HORIZONTAL;	
			}
			else{
				//__android_log_print(ANDROID_LOG_INFO, "adMOB", "STOPPED");
				frames=0;
				player_state=STOPPED;
			}
		}

	}
	else if(tempX==tileX){
		if(tileY<tempY){
			if(jumpTile){
				nextY+=2;
			}else{
				nextY++;
			}
		}else if (tileY>tempY){
			if(jumpTile){
				nextY-=2;
			}else{
				nextY--;
			}
		}
		if(	tmxLoader->isPassable(tileX,nextY) && !(tileX==nextX && tileY==nextY) ){
			tmxLoader->breakFloor(tileX,tileY);
			updateDestination(nextX, nextY);
			//__android_log_print(ANDROID_LOG_INFO, "adMOB", "MOVING_VERTICAL");
			frames=0;
			player_state=MOVING_VERTICAL;
		}		
		else{
			if(crossWall){
				updateDestination(nextX, nextY);
				//__android_log_print(ANDROID_LOG_INFO, "adMOB", "MOVING_VERTICAL");
				frames=0;
				player_state=MOVING_VERTICAL;
			}
			else{
				//__android_log_print(ANDROID_LOG_INFO, "adMOB", "STOPPED");
				frames=0;
				player_state=STOPPED;
			}
		}
	}else{
		player_state=STOPPED;
	}
}

void Player::updateDestination(int nextX, int nextY){
	stepX=nextX*92;
	stepY=nextY*92;
}


bool Player::arrival(){
	tileX=(int)(stepX+46)/92;
	tileY=(int)(stepY+46)/92;

	//__android_log_print(ANDROID_LOG_INFO, "adMOB","playerpos %d %d\n", tileX,tileY);

	if(tmxLoader->isPassable(tileX,tileY)){
		crossWall=false;
		jumpTile=false;
	}

	x=tileX*92;
	y=tileY*92;

	if(tmxLoader->isKey(tileX,tileY)){
		//__android_log_print(ANDROID_LOG_INFO, "adMOB","got key\n");
		hasKey=true;
		tmxLoader->keyOnMap=false;
	}

	if(tmxLoader->isDoor(tileX,tileY)){
		//__android_log_print(ANDROID_LOG_INFO, "adMOB","arrived at door\n");
		if(hasKey){
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","and has key!\n");	
			tmxLoader->changeTile(tileX,tileY,5);
		}
		else{
			//__android_log_print(ANDROID_LOG_INFO, "adMOB","but no key =(\n");	
		}
	}

	if(tmxLoader->isHole(tileX,tileY)){
		//__android_log_print(ANDROID_LOG_INFO, "adMOB","Player is dead!\n");
		return false; 
	}else{
		calculateNextMove();
	}

	return true;
}

void Player::die(){
	//__android_log_print(ANDROID_LOG_INFO, "adMOB","Player is dead!\n");
	//isAlive=false;
}


