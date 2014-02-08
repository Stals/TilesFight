//
//  Army.cpp
//  SampleGame
//
//  Created by Stanislav Korotaev on 2/8/14.
//  Copyright (c) 2014 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "Army.h"
#include "Game.h"

Army::Army(Hexagon* hex, int troopsCount, Point destination):
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

void Army::setCurrentHex(Hexagon* hex)
{
    currentHex = hex;
}

Point Army::getDestination()
{
    return destination;
}


void Army::move(float dt)
{
    // TODO тут должен быть только следующий в пути
    Hexagon* dest = Game::current().getBoard()->at(destination.x, destination.y);
    
    // зачем я передалывал на передачу туда массива если бы я мог просто много раз вызвать тот метод который был?
    // видимо мне очень хорошо подумал
    // Если я переделаю на перемещение из 1 хекса в другой
    // то потом смогу переделать на передвижение именно армии - и создавать саму армию из выбранного хексагоня для ее передвижения
    
    //TroopsMover::moveTroops(this, dest);
    
    
    // то что снизу написано занимается сам mover? потому что он же сейчас типо такого вещи делает - наверное да
    // но вот отниманием войск наверное сам хексагон должен думать как он это делает
    
}