#include "TMXLoader.h"
#include "EnemyManager.h"


const int TMXLoader::cols=8;
const int TMXLoader::rows=5;

TMXLoader::TMXLoader()
{
	int arr[] =
	{
		3 ,3 ,9 ,9 ,3 ,3 ,3 ,3,
		1 ,2 ,6 ,7 ,16,21 ,6 ,1,
		3 ,9 ,2 ,2 ,1 ,1 ,6 ,6,
		11,3 ,1 ,1 ,1 ,2 ,1 ,16,
		1 ,2 ,1 ,2 ,3 ,2 ,1 ,4

	};
	m_LayerData.assign(arr, arr + sizeof(arr) / sizeof(arr[0]) );

	decode_and_store_map_data();

	glLoadTileSet("tileset.png",tileset,92,92,512,512);  
	glLoadTileSet("saida.png",doorset,92,92,512,128);  
	glLoadTileSet("key_level.png",keyset,92,92,512,512);  
	glLoadTileSet("pisoquebrando.png",pisoquebrando,92,92,512,128);  

	frames=0;
	keyFrame=0;
	keyOnMap=true;
	doorFrame=0;

}

TMXLoader::~TMXLoader()
{
	m_LayerData.clear();

	std::vector<FloorBreakingAnimation*>::iterator iter = floorAnimations.begin();
	while (iter != floorAnimations.end())
	{
		delete * iter;  
		iter = floorAnimations.erase(iter); 
	}
	floorAnimations.clear();

}

void TMXLoader::cleanup()
{
}



void TMXLoader::decode_and_store_map_data()
{

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if(m_LayerData[col+row*cols]==11){
				EnemyManager::getSingleton()->addEnemy(this,Enemy::ENEMY_1,Enemy::DOWN,col,row);
				m_LayerData[col+row*cols]=1;
			}

			if(m_LayerData[col+row*cols]==16){
				EnemyManager::getSingleton()->addEnemy(this,Enemy::ENEMY_3,Enemy::STOP_DOWN,col,row);
				m_LayerData[col+row*cols]=1;
			}

		}

	} 
}


void TMXLoader::changeTile(int x, int y, int value){
	if(m_LayerData[x+y*cols]!=value){
		m_LayerData[x+y*cols]=value;
	}
}

void TMXLoader::breakFloor(int x, int y){
	if(m_LayerData[x+y*cols]!=8){
		for(int i=0;i<floorAnimations.size();i++){
			if(floorAnimations[i]->x==x && floorAnimations[i]->y==y)
				return;
		}

		changeTile(x,y,8);
		FloorBreakingAnimation* fba=new FloorBreakingAnimation();
		fba->currentFrame=0;
		fba->x=x;
		fba->y=y;
		floorAnimations.push_back(fba);
	}
}


bool TMXLoader::isPassable(int x, int y){
	if(x<0 || y<0 || x>=cols || y>=rows)
		return false;

	return m_LayerData[x+y*cols]!=3;
}

bool TMXLoader::isKey(int x, int y){
	return m_LayerData[x+y*cols]==21;
}

bool TMXLoader::isDoor(int x, int y){
	return m_LayerData[x+y*cols]==70;
}

bool TMXLoader::isHole(int x, int y){
	return m_LayerData[x+y*cols]==8;
}

void TMXLoader::paint(){
	frames++;

	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			if(m_LayerData[col+row*cols]==21){
				glSprite(col*92,row*92,0,&tileset[1]);
				if(keyOnMap){
					if(frames%5==0){
						keyFrame++;
					}
					
					if(keyFrame==17){
						keyFrame=0;
					}
					else if(keyFrame==13){
						keyFrame=15;
					}
					else if(keyFrame==8){
						keyFrame=10;
					}
					else if(keyFrame==4){
						keyFrame=5;
					}

					glSprite(col*92,row*92,0,&keyset[keyFrame]);
				}
			}
			else if(m_LayerData[col+row*cols]==4){
				if(!keyOnMap){
					if(frames%15==0){
						doorFrame++;
					}
					if(doorFrame>2){
						doorFrame=0;
					}
					glSprite(col*92,row*92,0,&doorset[doorFrame]);
				}else{
					glSprite(col*92,row*92,0,&tileset[m_LayerData[col+row*cols]-1]);
				}
			}
			else{				
				glSprite(col*92,row*92,0,&tileset[m_LayerData[col+row*cols]-1]);
			}	
		}
	}


	std::vector<FloorBreakingAnimation*>::iterator iter = floorAnimations.begin();
	while (iter != floorAnimations.end())
	{
		if(frames%15==0){
			(*iter)->currentFrame++;
		}
		if((*iter)->currentFrame>3){
			delete * iter;  
			iter = floorAnimations.erase(iter); 
			continue;
		}
		glSprite((*iter)->x*92,(*iter)->y*92,0,&pisoquebrando[(*iter)->currentFrame]);
		iter++;
	}
}