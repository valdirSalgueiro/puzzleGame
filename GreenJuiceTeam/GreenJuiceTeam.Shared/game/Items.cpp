#include "Items.h"

Items::Items(){
	spr=new glImage();
	glLoadTileSet("items.png",spr,128,128,128,128);  
}

Items::~Items(){
	delete spr;
}

void Items::draw(){
	glSprite(336,176,0,spr);
}