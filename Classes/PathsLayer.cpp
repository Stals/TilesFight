#include "PathsLayer.h"

#include <list>

#include "Hexagon.h"
#include "Army.h"
#include "Game.h"


PathsLayer::PathsLayer()
{
    CCLayer::init();
    autorelease();
    
    setTouchEnabled(true);
}


void PathsLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    //CCLog("begin");
    // TODO записывам куда-то чтобы потом нарисовать это в draw
    // причем записываем тупо что есть вот такой тач и все?
}

void PathsLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    Board* board = Game::current().getBoard();
    
    CCTouch* touch = 0;
    Hexagon* startHex = 0;
    Hexagon* endHex = 0;
    
    
    
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it){
		touch = ((CCTouch*)*it);
		startHex = 0;
		endHex = 0;
        
        board->getStartEndHex(touch, startHex, endHex);
        
        if(startHex && endHex){
            addTouch(startHex, endHex);
        }
        
    }
}

void PathsLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    findAndRemoveTouches(pTouches);
}

void PathsLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    findAndRemoveTouches(pTouches);
}

void PathsLayer::findAndRemoveTouches(CCSet *pTouches)
{
    Board* board = Game::current().getBoard();
    
    CCTouch* touch = 0;
    Hexagon* startHex = 0;
    Hexagon* endHex = 0;
    
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it){
		touch = ((CCTouch*)*it);
		startHex = 0;
		endHex = 0;
        
        board->getStartEndHex(touch, startHex, endHex);
        
        if(startHex){
            removeTouch(startHex);
        }
    }
}

void PathsLayer::addTouch(Hexagon* startHex, Hexagon* endHex)
{
    touchesBegan[startHex] = endHex;
}

void PathsLayer::removeTouch(Hexagon* startHex)
{
    TouchesContainer::iterator it =  touchesBegan.find(startHex);
    
    if(it != touchesBegan.end()){
        touchesBegan.erase(it);
    }
}

Hexagon* PathsLayer::getEndPointForUser(Player* player)
{
    TouchesContainer::iterator it = touchesBegan.begin();
    TouchesContainer::iterator end = touchesBegan.end();
    
    for(; it != end; ++it){
        if(it->first->getOwner() == player){
            return it->second;
        }
    }
    
    return 0;
}




void PathsLayer::draw(){
    drawArmies();
    drawTouches();
}

void PathsLayer::drawPath(const std::list<Hexagon*>& path)
{
    glLineWidth(7.0f);
    
    if(!path.empty()){
        ccColor3B playerColor = path.front()->getOwner()->getColor();
        cocos2d::ccDrawColor4B(playerColor.r, playerColor.g, playerColor.b, 255);
        
    }else{
        return;
    }
    
    std::list<Hexagon*>::const_iterator hexEnd = path.end();
    std::list<Hexagon*>::const_iterator hexPrev = path.begin();
    std::list<Hexagon*>::const_iterator hexIt = ++path.begin();
    
    for(; hexIt != hexEnd; ++hexIt){
        cocos2d::ccDrawLine((*hexPrev)->getPosition(), (*hexIt)->getPosition());
        hexPrev = hexIt;
    }

}

void PathsLayer::drawArmies()
{
    glLineWidth(7.0f);
    
    const std::list<Army*>& armies = Game::current().getArmies();
    
    std::list<Army*>::const_iterator armyEnd = armies.end();
    std::list<Army*>::const_iterator armyIt = armies.begin();
    for(; armyIt != armyEnd; ++armyIt){
        
        const std::list<Hexagon*>& path = (*armyIt)->getCurrentPath();
        drawPath(path);
    }
}

void PathsLayer::drawTouches()
{
    Hexagon* endHex = 0;
    Player* player = 0;
   
    std::vector<Player*>& players = Game::current().getPlayers();
    const size_t playersCount = players.size();
   
    for(size_t playerID = 0; playerID < playersCount; ++playerID){
        player = players[playerID];
        endHex = getEndPointForUser(player);
        if(endHex){
            drawPlayersSelected(player, endHex);
        }
    }
}

void PathsLayer::drawPlayersSelected(Player* player, Hexagon* endHex)
{
    // TODO move geting board out of here?
    Board* board = Game::current().getBoard();
    Hexagon* startHex = 0;
    
    std::vector<Hexagon*> selectedHexagons = player->getSelectedHexagons();
    const size_t selectedCount = selectedHexagons.size();
    
    for(size_t i = 0; i < selectedCount; ++i){
        startHex = selectedHexagons[i];
        
        std::list<Hexagon*> path = board->getPath(startHex, endHex);
        path.push_front(startHex);
        drawPath(path);
    }
}

