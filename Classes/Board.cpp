#include "Board.h"

#define HEX_SIZE 64.f

Board::Board(int width, int height):width(width), height(height){
	CCLayer::init();
	autorelease();
	setTouchEnabled(true);

	initBoard();
}

void Board::initBoard()
{
	for(int y = 0; y < height; ++y){
		const int w = (y%2) == 0 ? width :width - 1; 
		for(int x = 0; x < w; ++x){
			Hexagon* hex = new Hexagon;
			hex->setScale(HEX_SIZE / hex->getContentSize().width);
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