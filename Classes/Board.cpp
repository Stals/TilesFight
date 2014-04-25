#include "Board.h"
#include "Addons/TroopsGenerator.h"
#include "AStar.h"
#include "Game.h"
#include "Army.h"
#include "Sound.h"
#include "EffectPlayer.h"
#include "PathsLayer.h"

#define HEX_SIZE 64.f //80?

Board::Board(int width, int height): width(width), height(height), pathsLayer(0){
	CCLayer::init();
	autorelease();
	setTouchEnabled(true);

	initBoard();
    setupPaths();
}

Board::~Board()
{
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
			this->addChild(hex, zHexagon);

		}	
	}
}

void Board::setupPaths()
{
    pathsLayer = new PathsLayer;
    this->addChild(pathsLayer, zPath);
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
					if(hex->isSelectable()){
                        hex->setSelected(true);
                        EffectPlayer::playSelectionEffect();
                        hex->tapped();
                    }
					break;
                    
				}
			}		
		}
	
	}
}


void Board::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    // select hexagon if not yet selected
    
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it){
		CCTouch* touch = ((CCTouch*)*it);
		Hexagon* startHex = 0;
		Hexagon* endHex = 0;
        
		getStartEndHex(touch, startHex, endHex);
        if(!startHex) break;
        if(!endHex) continue;
        
        Player* owner = startHex->getOwner();
        if(owner){
            if(owner == endHex->getOwner()){
                if(endHex->isSelectable() && (!endHex->isSelected())){
                    endHex->setSelected(true);
                    EffectPlayer::playSelectionEffect();
                }
            }
            setEndPoint(owner, convertTouchToNodeSpace(touch));
        }
        
    }
    
    // add lines for drawing
    
    /*clearLines();
    CCTouch* touch = ((CCTouch*)*pTouches->begin());
    std::vector<Player*> players = Game::current().getPlayers();

    for(size_t playerID = 0; playerID < players.size(); ++playerID){
        //TODO  тут нужно получить touch который именно для этого игрока!!!
        
        
        std::vector<Hexagon*> selectedHexagons = players[playerID]->getSelectedHexagons();
        
        for(size_t hexID = 0; hexID < selectedHexagons.size(); ++hexID){
            Hexagon* startHex = selectedHexagons[hexID];
            Player* owner = startHex->getOwner();
            
            addLine(owner, startHex->getPosition());
        }
    }*/
}

void Board::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    clearLines();

	for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it){
		CCTouch* touch = ((CCTouch*)*it);
		Hexagon* startHex = 0;
		Hexagon* endHex = 0;

		getStartEndHex(touch, startHex, endHex);
        
        std::vector<Hexagon*> selectedHexagons;
		if(startHex && startHex->getOwner() && (startHex->getOwner()->isHexagonsSelectable())){
            selectedHexagons = startHex->getOwner()->getSelectedHexagons();
            startHex->getOwner()->deselectAllHexagons();
        }else{
            continue;
        }

        if((!startHex) || (!endHex)) continue;

        // Note: we need to create and move armies in 2 cycles so thar they will not travel all the way
        std::vector<Army*> armies(selectedHexagons.size());
        // create armies
        for(size_t i = 0; i < selectedHexagons.size(); ++i){
            armies[i] = selectedHexagons[i]->createArmy(endHex);
        }
        
        // move armies
        for(size_t i = 0; i < armies.size(); ++i){
            armies[i]->move(0);
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


void Board::addLine(Player* player, const CCPoint &start){
    lines[player].starts.push_back(start);
}

void Board::clearLines()
{
    std::multimap<Player*, LinesData>::iterator it = lines.begin();
    for(; it != lines.end(); ++it){
        it->second.starts.clear();
    }
}
    
void Board::setEndPoint(Player* player, const CCPoint &endPoint)
{
    lines[player].end = endPoint;
}
