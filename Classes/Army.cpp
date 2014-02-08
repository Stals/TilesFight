//
//  Army.cpp
//  SampleGame
//
//  Created by Stanislav Korotaev on 2/8/14.
//  Copyright (c) 2014 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "Army.h"
#include "Game.h"

Army::Army(Hexagon* hex, int troopsCount, Hexagon* destination):
currentHex(hex), troopsCount(troopsCount), destination(destination)
{
 
    // TODO create scheduler
}

// TODO unschedule

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


void Army::move(float dt)
{
    Hexagon* nextHex = NULL;
    if(currentHex == destination){
        nextHex = currentHex;
    }else{
        std::list<Hexagon*> path = Game::current().getBoard()->getPath(currentHex, destination);
        if(!path.empty())
            nextHex = path.front();
    }
    
    if(nextHex)
        TroopsMover::moveTroops(this, nextHex);
    
}