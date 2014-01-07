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
	
	/*int x = 1;
	int y = 7;

	hexArray2D.at(x,y)->setColor(hexGreen);

	for(int side = 0; side < HexSidesCount; ++side)
	{
		Hexagon* hex = hexArray2D.sideHexAt((HexSide)side, x, y);
		if(hex){
			hex->setColor(hexGreen);	
		}
	}*/

}



void Board::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it){
		for(size_t y = 0; y < hexArray2D.size(); ++y){
			HexArray *row = hexArray2D.row(y);
			
			for(size_t x = 0; x < row->size(); ++x){
				Hexagon* hex = row->at(x);
				if(hex->containsTouchLocation((CCTouch*)*it)){
					hex->setColor(hexRed);
					break;
					// TODO нужно найти способ выходит и из цикла y - т.к. это лишнее
				}			
			}		
		}
	
	}
}

void Board::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
}

void Board::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
}

void Board::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
}

/*
	TODO тутже нужно будет делать хитрые штуки с touch moved с понимаением что он уже выделил - либо тупо делать им setSelected()
	а потом делать getSelectedHexagons() который вернет hexArray с которым я могу уже что угодно делать
*/