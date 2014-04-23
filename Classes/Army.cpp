//
//  Army.cpp
//  SampleGame
//
//  Created by Stanislav Korotaev on 2/8/14.
//  Copyright (c) 2014 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "Army.h"
#include "Game.h"

#define MOVE_DELAY 1.5f

Army::Army(Hexagon* hex, int troopsCount, Hexagon* destination, bool selected):
currentHex(hex), troopsCount(troopsCount), destination(destination), selected(selected)
{
    CCSprite::init();
    autorelease();
        
    this->schedule(schedule_selector(Army::move), MOVE_DELAY);
    
    Game::current().addArmy(this);
}

Army::~Army()
{
}

Hexagon* Army::getCurrentHex()
{
    return currentHex;
}

int Army::getTroopsCount()
{
    return troopsCount;
}

void Army::removeTroops(int count)
{
    troopsCount -= count;
}


void Army::setCurrentHex(Hexagon* hex)
{
    currentHex = hex;
}

Hexagon* Army::getDestination()
{
    return destination;
}

void Army::setSelected(bool selected){
    this->selected = selected;
}

bool Army::isSelected()
{
    return selected;
}

void Army::move(float dt)
{
    Hexagon* nextHex = NULL;
    if(currentHex == destination){
        nextHex = currentHex;
    }else{
        currentPath = Game::current().getBoard()->getPath(currentHex, destination);
        if(!currentPath.empty())
            nextHex = currentPath.front();
    }
    
    if(nextHex)
        TroopsMover::moveTroops(this, nextHex);
    
}

void Army::free()
{
    Game::current().removeArmy(this);
    removeFromParentAndCleanup(true);
}

const std::list<Hexagon*>& Army::getCurrentPath()
{
    return currentPath;
}