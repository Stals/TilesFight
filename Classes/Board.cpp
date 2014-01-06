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
		hexArray2D.addRow();

		const int w = (y%2) == 0 ? width :width - 1; 
		for(int x = 0; x < w; ++x){
			Hexagon* hex = new Hexagon;
			hex->setScale(HEX_SIZE / hex->getContentSize().width);
			
			if((y % 2) == 0){
				hex->setPositionX(x * scaledWidth(hex));
			}else{
				hex->setPositionX((x * scaledWidth(hex)) + (scaledWidth(hex) / 2));
			}
			hex->setPositionY(y * (scaledHeight(hex) * 3/4));

			hexArray2D.row(y)->push_back(hex);
			this->addChild(hex);
		}	
	}

	int x = 2;
	int y = 1;

	hexArray2D.at(x,y)->setColor(hexGreen);

	for(int side = 0; side < HexSidesCount; ++side)
	{
		Hexagon* hex = hexArray2D.sideHexAt((HexSide)side, x, y);
		if(hex){
			hex->setColor(hexRed);	
		}
	}

}