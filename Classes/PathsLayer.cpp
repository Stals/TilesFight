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
    //CCLog("move");
}

void PathsLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    //CCLog("end");
}

void PathsLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
}

void PathsLayer::draw(){
    //glEnable(GL_LINE_SMOOTH);
    /*glLineWidth(3.0f);
     for(std::map<Player*, LinesData>::iterator it = lines.begin(); it != lines.end(); ++it){
     Player* player = it->first;
     if(player->isAI()) {
     continue;
     }
     ccColor3B playerColor = player->getColor();
     cocos2d::ccDrawColor4B(playerColor.r, playerColor.g, playerColor.b, 255);
     
     LinesData& linesData = it->second;
     for(size_t i = 0; i < linesData.starts.size(); ++i){
     cocos2d::ccDrawLine(linesData.starts[i], linesData.end);
     //cocos2d::ccDrawCircle(it->second.start, 29, CC_DEGREES_TO_RADIANS(360), 60, false, 1, 1);
     }
     
     if(!linesData.starts.empty()){
     cocos2d::ccDrawCircle(linesData.end, 6, CC_DEGREES_TO_RADIANS(360), 60, false, 1, 1);
     }
     }*/
    
    glLineWidth(7.0f);
    
    const std::list<Army*>& armies = Game::current().getArmies();
    
    std::list<Army*>::const_iterator armyEnd = armies.end();
    std::list<Army*>::const_iterator armyIt = armies.begin();
    for(; armyIt != armyEnd; ++armyIt){
        
        const std::list<Hexagon*>& path = (*armyIt)->getCurrentPath();
        
        if(!path.empty()){
            ccColor3B playerColor = path.front()->getOwner()->getColor();
            cocos2d::ccDrawColor4B(playerColor.r, playerColor.g, playerColor.b, 255);
            
        }else{
            continue;
        }
        
        std::list<Hexagon*>::const_iterator hexEnd = path.end();
        std::list<Hexagon*>::const_iterator hexPrev = path.begin();
        std::list<Hexagon*>::const_iterator hexIt = ++path.begin();
        
        for(; hexIt != hexEnd; ++hexIt){
            cocos2d::ccDrawLine((*hexPrev)->getPosition(), (*hexIt)->getPosition());
            hexPrev = hexIt;
        }
    }
}
