#include "Items.h"

Items::Items(){
	spr=new glImage();
	glLoadTileSet("items.png",spr,400, 400, 400, 400);
}

Items::~Items(){
	delete spr;
}

void Items::draw(){
	glSprite(336,176,0,spr);
}