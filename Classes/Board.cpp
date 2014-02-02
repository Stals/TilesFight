#include "Board.h"
#include "Addons/TroopsGenerator.h"
#include "CCShake.h"
#include "AStar.h"

#define HEX_SIZE 64.f //80?

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

std::list<Hexagon*> Board::getPath(Hexagon* start, Hexagon* end)
{
    AStar astar;
    return astar.findPath(start, end);
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


void Board::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{

    /*
     // Path finding debug
    for(size_t y = 0; y < hexArray2D.size(); ++y){
        HexArray *row = hexArray2D.row(y);
        
        for(size_t x = 0; x < row->size(); ++x){
            Hexagon* hex = row->at(x);
            hex->setColor(ccc3(0,0,0));
            
        }
    }*/
    
    //lines.clear();
    /*
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it){
		CCTouch* touch = ((CCTouch*)*it);
		Hexagon* startHex = 0;
		Hexagon* endHex = 0;
        
		getStartEndHex(touch, startHex, endHex);
        
        //std::list<Hexagon*> path = getPath(startHex, endHex);
        //for(std::list<Hexagon*>::iterator it = path.begin(); it != path.end(); ++it){
        //    (*it)->setColor(ccc3(255, 255, 255));
        //    (*it)->setOpacity(255);
        //}
        
        
        std::vector<Hexagon*> selectedHexagons =
    */
        
        /*if(startHex)
        lines.insert(std::make_pair(startHex->getOwner(), LineData(startHex->getOwner()->getColor(), startHex->getPosition(), convertTouchToNodeSpace(touch))));
        
    }*/
    
    // select hexagon if not yet selected
    
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it){
		CCTouch* touch = ((CCTouch*)*it);
		Hexagon* startHex = 0;
		Hexagon* endHex = 0;
        
		getStartEndHex(touch, startHex, endHex);
        if(!startHex) break;
        if(!endHex) continue;
        
        Player* owner = startHex->getOwner();
        if(owner == endHex->getOwner()){
            endHex->setSelected(true);
        }
        
    }
    
    
    
    // add lines for drawing
    /*
    lines.clear();

    for( all players){ // добавить в GAME?
        //TODO  тут нужно получить touch который именно для этого игрока!!!
        
        
        get selectedHexagons
        
        for(all selectedHexagons){
            lines.insert(std::make_pair(startHex->getOwner(), LineData(startHex->getOwner()->getColor(), startHex->getPosition(), convertTouchToNodeSpace(touch))));
            
        }
    }*/
}

void Board::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    lines.clear();

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

	//if(!hexArray2D.areConnected(startHex, endHex)) return;
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
void Board::draw(){
    
    
    glLineWidth(5.0f);
    glEnable(GL_LINE_SMOOTH);
    for(std::multimap<Player*, LineData>::iterator it = lines.begin(); it != lines.end(); ++it){
        cocos2d::ccDrawColor4B(it->second.color.r, it->second.color.g, it->second.color.b, 255);
        //cocos2d::ccDrawCircle(it->second.start, 29, CC_DEGREES_TO_RADIANS(360), 60, false, 1, 1);
        cocos2d::ccDrawLine(it->second.start, it->second.end);
        cocos2d::ccDrawCircle(it->second.end, 6, CC_DEGREES_TO_RADIANS(360), 60, false, 1, 1);
    }
}
