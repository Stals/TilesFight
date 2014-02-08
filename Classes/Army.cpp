//
//  Army.cpp
//  SampleGame
//
//  Created by Stanislav Korotaev on 2/8/14.
//  Copyright (c) 2014 Bullets in a Burning Box, Inc. All rights reserved.
//

#include "Army.h"
#include "Game.h"

Army::Army(Hexagon* hex, Point destination):
currentHex(hex), destination(destination)
{
    
}


void Army::move(float dt)
{
    Hexagon* dest = Game::current().getBoard()->at(destination.x, destination.y);
    
    // зачем я передалывал на передачу туда массива если бы я мог просто много раз вызвать тот метод который был?
    // видимо мне очень хорошо подумал
    // Если я переделаю на перемещение из 1 хекса в другой
    // то потом смогу переделать на передвижение именно армии - и создавать саму армию из выбранного хексагоня для ее передвижения
    
    /*Game::current().getBoard()->moveTroops(<#std::vector<Hexagon *> &selectedHexagons#>, <#Hexagon *endHex#>)
    
    hex->removeArmy(this);
    dest->addArmy(this);
    hex = dest;*/
    
}