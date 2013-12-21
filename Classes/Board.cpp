#include "Board.h"

//#define HEX_SIZE 64.f

Board::Board(int width, int height):width(width), height(height){
	CCLayer::init();
	autorelease();

	initBoard();
}

void Board::initBoard()
{
	for(int y = 0; y < height; ++y){
		for(int x = 0; x < width; ++x){
			Hexagon* hex = new Hexagon;
			hex->setScale(0.25f);
			this->addChild(hex);
		
			if((y % 2) == 0){
				hex->setPositionX(x * scaledWidth(hex));
			}else{
				hex->setPositionX((x * scaledWidth(hex)) + (scaledWidth(hex) / 2));
			}

			hex->setPositionY(y * (scaledHeight(hex) * 3/4));
		}	
	}
}