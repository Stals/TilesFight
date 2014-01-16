#include "Board.h"
#include "TroopsGenerator.h"

#define HEX_SIZE 64.f

Board::Board(int width, int height):width(width), height(height){
	CCLayer::init();
	autorelease();
	setTouchEnabled(true);

	initBoard();
}

Hexagon* Board::at(size_t x, size_t y)
{
	return hexArray2D.at(x, y);
}

Hexagon* Board::sideHexAt(HexSide side, size_t x, size_t y)
{
	return hexArray2D.sideHexAt(side, x, y);
}


void Board::initBoard()
{
	for(int y = 0; y < height; ++y){
		hexArray2D.addRow();

		const int w = (y%2) == 0 ? width :width - 1; 
		for(int x = 0; x < w; ++x){
			Hexagon* hex = new Hexagon(x, y);
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
}



void Board::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it){
		CCTouch* touch = ((CCTouch*)*it);

		for(size_t y = 0; y < hexArray2D.size(); ++y){
			HexArray *row = hexArray2D.row(y);
			
			for(size_t x = 0; x < row->size(); ++x){				
				Hexagon* hex = row->at(x);
				if(hex->getOwner() && hex->getOwner()->isAI()) continue;

				if(hex->containsTouchLocation(touch)){
					hex->toggleSelected();
					//hex->setColor(hexRed);
					//hex->addTroops(rand() % 100);
					break;
					// TODO нужно найти способ выходит и из цикла y - т.к. это лишнее
				}			
			}		
		}
	
	}
}

/*
	TODO тутже нужно будет делать хитрые штуки с touch moved с понимаением что он уже выделил - либо тупо делать им setSelected()
	а потом делать getSelectedHexagons() который вернет hexArray с которым я могу уже что угодно делать
*/

void Board::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	/*
		TODO из пердведущей точки получить owner'a и его какраз и замутить
	*/
}

void Board::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it){
		CCTouch* touch = ((CCTouch*)*it);
		Hexagon* startHex = 0;
		Hexagon* endHex = 0;

		getStartEndHex(touch, startHex, endHex);
		if(startHex->getOwner() && startHex->getOwner()->isAI()) continue;

		moveTroops(startHex, endHex);
	}
}

void Board::moveTroops(Hexagon * startHex, Hexagon* endHex)
{
	startHex->toggleSelected();

	if(!hexArray2D.areConnected(startHex, endHex)) return;
	if(startHex->getTroopsCount() <= 1) return;

	// TODO добавить атаку
	if(startHex != endHex){
		const int troops = startHex->getTroopsCount() - 1;
		startHex->removeTroops(troops);

		if(endHex->getOwner() == startHex->getOwner()){
			endHex->addTroops(troops);
		}else{
			if(troops == endHex->getTroopsCount()){
				endHex->removeTroops(troops);
				endHex->setOwner(0); // TODO NoPlayer который уже = 0?
			}else if(troops < endHex->getTroopsCount()){
				endHex->removeTroops(troops);			
			}else{ // troops > endHex->getTroopsCount()
				const int firstPlayerTroopsLeft = troops - endHex->getTroopsCount();
				endHex->removeTroops(endHex->getTroopsCount());
				endHex->addTroops(firstPlayerTroopsLeft);
				endHex->setOwner(startHex->getOwner());
			}
		}
	}
}

void Board::getStartEndHex(CCTouch* touch, Hexagon*& startHex, Hexagon*& endHex)
{
	for(size_t y = 0; y < hexArray2D.size(); ++y){
		HexArray *row = hexArray2D.row(y);
			
		for(size_t x = 0; x < row->size(); ++x){
			Hexagon* hex = row->at(x);	
			if(hex->containsTouchLocation(touch->getStartLocation())){
				startHex = hex;
				if(startHex && endHex) return;
			}
			// Note: не else if - так как он может быть и стартом и концом
			if(hex->containsTouchLocation(touch->getLocation())){
				endHex = hex;
				if(startHex && endHex) return;
			}				
		}			
	}
}

void Board::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
}
