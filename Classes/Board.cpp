#include "Board.h"
#include "Addons/TroopsGenerator.h"
#include "CCShake.h"

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

Hexagon* Board::sideHexAt(HexSide side, Hexagon* hex)
{
    return sideHexAt(side, hex->getXCoord(), hex->getYCoord());
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
					// TODO ÌÛÊÌÓ Ì‡ÈÚË ÒÔÓÒÓ· ‚˚ıÓ‰ËÚ Ë ËÁ ˆËÍÎ‡ y - Ú.Í. ˝ÚÓ ÎË¯ÌÂÂ
				}			
			}		
		}
	
	}
}

/*
	TODO ÚÛÚÊÂ ÌÛÊÌÓ ·Û‰ÂÚ ‰ÂÎ‡Ú¸ ıËÚ˚Â ¯ÚÛÍË Ò touch moved Ò ÔÓÌËÏ‡ÂÌËÂÏ ˜ÚÓ ÓÌ ÛÊÂ ‚˚‰ÂÎËÎ - ÎË·Ó ÚÛÔÓ ‰ÂÎ‡Ú¸ ËÏ setSelected()
	‡ ÔÓÚÓÏ ‰ÂÎ‡Ú¸ getSelectedHexagons() ÍÓÚÓ˚È ‚ÂÌÂÚ hexArray Ò ÍÓÚÓ˚Ï ˇ ÏÓ„Û ÛÊÂ ˜ÚÓ Û„Ó‰ÌÓ ‰ÂÎ‡Ú¸
*/

void Board::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	/*
		TODO ËÁ ÔÂ‰‚Â‰Û˘ÂÈ ÚÓ˜ÍË ÔÓÎÛ˜ËÚ¸ owner'a Ë Â„Ó Í‡Í‡Á Ë Á‡ÏÛÚËÚ¸
	*/
}

void Board::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it){
		CCTouch* touch = ((CCTouch*)*it);
		Hexagon* startHex = 0;
		Hexagon* endHex = 0;

		getStartEndHex(touch, startHex, endHex);
		if(startHex) startHex->setSelected(false);

        if((!startHex) || (!endHex)) continue;
		if(startHex && startHex->getOwner() && startHex->getOwner()->isAI()) continue;

		moveTroops(startHex, endHex);
	}
}

void Board::moveTroops(Hexagon * startHex, Hexagon* endHex)
{
	startHex->setSelected(false);

	if(!hexArray2D.areConnected(startHex, endHex)) return;
	if(startHex->getTroopsCount() <= 1) return;

	// TODO ‰Ó·‡‚ËÚ¸ ‡Ú‡ÍÛ
	if(startHex != endHex){
		const int troops = startHex->getTroopsCount() - 1;
		startHex->removeTroops(troops);

		if(endHex->getOwner() == startHex->getOwner()){
			endHex->addTroops(troops);
		}else{
			if(troops == endHex->getTroopsCount()){
				endHex->removeTroops(troops);
				endHex->changeOwner(0); // TODO NoPlayer ÍÓÚÓ˚È ÛÊÂ = 0?
			}else if(troops < endHex->getTroopsCount()){
				endHex->removeTroops(troops);			
			}else{ // troops > endHex->getTroopsCount()
				const int firstPlayerTroopsLeft = troops - endHex->getTroopsCount();
				endHex->removeTroops(endHex->getTroopsCount());
				endHex->addTroops(firstPlayerTroopsLeft);
				endHex->changeOwner(startHex->getOwner());
			}
            //shakeAround(endHex, 2);
		}
		if(endHex->getTroopsCount() > 0){
			endHex->runScaleAction();
		}
	}
    
}


int Board::getWidth(size_t row)
{
	if(row % 2 == 0){
		return width;
	}else{
		return width - 1;
	}
}

int Board::getHeight()
{
	return height;
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
			// Note: ÌÂ else if - Ú‡Í Í‡Í ÓÌ ÏÓÊÂÚ ·˚Ú¸ Ë ÒÚ‡ÚÓÏ Ë ÍÓÌˆÓÏ
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

void Board::shakeAround(const Hexagon *hex, int strength)
{
    
    const float dt = 0.5f;

    // Shake around
    /*for(int side = 0; side < HexSidesCount; ++side)
	{
		Hexagon* h = sideHexAt((HexSide)side, hex->getXCoord(), hex->getYCoord());
		if(h){
            h->runAction(CCEaseIn::create(CCShake::actionWithDuration(dt, strength), dt));
        }
    }*/

    // shake all
    runAction(CCEaseIn::create(CCShake::actionWithDuration(dt, strength), dt));
    

}
